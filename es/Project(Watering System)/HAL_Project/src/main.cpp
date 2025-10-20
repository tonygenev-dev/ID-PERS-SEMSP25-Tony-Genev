#include "main.h"
#include <stdio.h>
#include <string.h>


UART_HandleTypeDef huart2;
TIM_HandleTypeDef htim2; // microsecond counter
TIM_HandleTypeDef htim3; // PWM for TRIG
ADC_HandleTypeDef hadc1;// Moisture sensor analog input
TIM_HandleTypeDef htim4; // PWM for pump

// Ultrasonic measurement
volatile uint32_t rising_time = 0;
volatile uint32_t falling_time = 0;
volatile uint32_t echo_time = 0;
volatile uint8_t echo_event_flag = 0; // 1 = rising, 2 = falling
volatile uint32_t echo_event_time = 0;
uint32_t distance_mm = 0;
//
#define Pump_Speed 300 // 300 for ~30% duty cycle

char txBuf[64];

// Prototypes
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM4_Init(void);
static uint32_t read_moisture_percent(void);

// EXTI callback forward declared by HAL
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

// Main
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_ADC1_Init();

    // Start TIM2 as microsecond counter
    HAL_TIM_Base_Start(&htim2);

    // Start PWM on TIM3 to generate TRIG pulses automatically
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    // Start pump PWM (channel configured but duty 0 initially)
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

    sprintf(txBuf, "Ultrasonic + Moisture Sensor Test\r\nSystemCoreClock = %lu\r\n", SystemCoreClock);
    HAL_UART_Transmit(&huart2, (uint8_t*)txBuf, strlen(txBuf), HAL_MAX_DELAY);

    uint8_t pump_active = 0;
    

    while (1)
    {
        // Small delay to let PWM trigger and ECHO capture happen
        HAL_Delay(60);

        // Read moisture immediately (near the same time as ultrasonic)
        uint32_t moisture = read_moisture_percent();

        // Compute distance if we have an echo measurement
        // Compute distance if we have an echo measurement
if (echo_time != 0)
{
    distance_mm = (343 * echo_time) / 2000;
}
else
{
    distance_mm = 0; // no valid measurement
}

// Control LED based on distance
if (distance_mm != 0 && distance_mm >= 100) 
{
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); // LED ON
}
else
{
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET); // LED OFF
}


    // Print both values every cycle (or you can filter/change frequency)
        if (distance_mm == 0)
            sprintf(txBuf, "Distance: -- mm  Moisture: %lu %%\r\n", (unsigned long)moisture);
        else
            sprintf(txBuf, "Distance: %lu mm  Moisture: %lu %%\r\n", (unsigned long)distance_mm, (unsigned long)moisture);

        HAL_UART_Transmit(&huart2, (uint8_t*)txBuf, strlen(txBuf), HAL_MAX_DELAY);

        // Pump control: if moisture < 50% start pump at 50% duty, else stop
        if (moisture < 50)
        {
            if (!pump_active)
            {
                // Period set to 1000 -> 50% duty => 500
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Pump_Speed);
                pump_active = 1;
            }
        }
        else
        {
            if (pump_active)
            {
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
                pump_active = 0;
            }
        }

        // Clear echo_time so next reading requires a new capture
        echo_time = 0;

        HAL_Delay(140); // ~200 ms between prints
        // read_moisture_raw_and_percent();
    }

    // should never reach
    return 0;
}

// ----------------- ADC -----------------
static void MX_ADC1_Init(void)
{
    __HAL_RCC_ADC12_CLK_ENABLE();

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4; // 18 MHz ADC clock (72MHz/4) accurate
    hadc1.Init.Resolution = ADC_RESOLUTION_12B; // 12-bit (0..4095) 0v to 3.3V
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;// software start manually
    HAL_ADC_Init(&hadc1);

    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_2; // PA1 -> ADC_IN2
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5; //19.5 cycles (fast but accurate enough)
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

static uint32_t read_moisture_percent(void)
{
    uint32_t raw = 0;
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        raw = HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Stop(&hadc1);

    // Convert raw (0..4095) to percent (0..100)
    uint32_t percent = (raw * 100) / 4095;
    return percent;
}

// ----------------- EXTI callback -----------------
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == ECHO_Pin)
    {
        uint32_t cnt = __HAL_TIM_GET_COUNTER(&htim2);
        if (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET)
        {
            rising_time = cnt;
        }
        else
        {
            falling_time = cnt;
            if (falling_time >= rising_time)
                echo_time = falling_time - rising_time;
            else
                echo_time = (65535 - rising_time + falling_time + 1); //total - high + low + 1(counts from 0)
        }
    }
}

// ----------------- TIM3 PWM for TRIG -----------------
static void MX_TIM3_Init(void)
{
    __HAL_RCC_TIM3_CLK_ENABLE();
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 71;         // 1 MHz → 1 µs tick 71+1 MHz STM32 system clock
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP; // Upcounting 0 to Period
    htim3.Init.Period = 59999;         // 60 ms period so that I avoid overflap 
    HAL_TIM_PWM_Init(&htim3);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;  
    sConfigOC.Pulse = 10;              // 10 µs signal stays HIGH this is the minimum for ultrasonic TRIG
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH; // Active HIGH
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE; // No fast mode
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
}

// ----------------- TIM2 microsecond counter -----------------
static void MX_TIM2_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 71;         // 1 MHz → 1 µs tick
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 65535;         // Max period
    HAL_TIM_Base_Init(&htim2);

    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}

// ----------------- USART2 -----------------
static void MX_USART2_UART_Init(void)
{
    __HAL_RCC_USART2_CLK_ENABLE();
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 38400;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);
}

// ----------------- GPIO -----------------
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ECHO pin (PA0) input with EXTI
    GPIO_InitStruct.Pin = ECHO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ECHO_GPIO_Port, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    // TRIG pin (PB4) as AF for TIM3_CH1 PWM
    GPIO_InitStruct.Pin = TRIG_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(TRIG_GPIO_Port, &GPIO_InitStruct);

    // Pump PWM on PB6 (TIM4_CH1) - alternate function
    GPIO_InitStruct.Pin = PUMP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(PUMP_GPIO_Port, &GPIO_InitStruct);

    // Moisture sensor pin PA4 -> analog
    GPIO_InitStruct.Pin = MOISTURE_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(MOISTURE_GPIO_Port, &GPIO_InitStruct);

    // LED pin as output
    GPIO_InitStruct.Pin = LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

// ----------------- TIM4 PWM for pump -----------------
static void MX_TIM4_Init(void)
{
    __HAL_RCC_TIM4_CLK_ENABLE();
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 71; // 71 + 1 MHz STM32 system clock -> 1 MHz timer clock
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 999; // 1000 steps  1000 = 100% duty cycle
    HAL_TIM_PWM_Init(&htim4);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0; // start off
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
}

// ----------------- CLOCK -----------------
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|
                                  RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

// ----------------- ERROR HANDLER -----------------
void Error_Handler(void)
{
    __disable_irq();
    while(1) {}
}
