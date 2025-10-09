#include <Arduino.h>
//Use only core 1 for now
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Pins
static const int led_pin = LED_BUILTIN;

//blink LED
void toggleLED(void *parameter){
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    Serial.printf("[%lu ms] LED is blinking\n", millis());
  }
}

void toggleLED_different(void *parameter){
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    Serial.printf("[%lu ms] LED_2 is blinking\n", millis());

  }
}

void some_text(void *parameter){
 
  while(1){
    Serial.printf("[%lu ms] Hello from another task\n", millis());
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);

  //Task to run forever
  xTaskCreatePinnedToCore(
              toggleLED,    //Function to be called
              "Toggle LED", //Name of task
              2048,         //Stack size (bytes in ESP32,words in FreeRTOS)
              NULL,         //Parameter to pass to function
              1,            //Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         //Task handle
              app_cpu);      //Run on one core for now
  
  xTaskCreatePinnedToCore(
              toggleLED_different,    //Function to be called
              "Toggle LED diff", //Name of task
              2048,         //Stack size (bytes in ESP32,words in FreeRTOS)
              NULL,         //Parameter to pass to function
              4,            //Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         //Task handle
              app_cpu);      //Run on one core for now

  

  xTaskCreatePinnedToCore(
              some_text,    //Function to be called
              "Some text", //Name of task
              2048,         //Stack size (bytes in ESP32,words in FreeRTOS)
              NULL,         //Parameter to pass to function
              2,            //Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         //Task handle
              app_cpu);      //Run on one core for now
}

void loop() {
  // put your main code here, to run repeatedly:

}
