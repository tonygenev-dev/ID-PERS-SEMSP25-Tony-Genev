#include <Arduino.h>

// Use only core 1 for now
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Pins
static const int led_pin = LED_BUILTIN;

// Queue handle
QueueHandle_t xQueue;

// Task: blink LED and send its state
void toggleLED(void *parameter) {
  bool led_state = false;

  while (1) {
    led_state = !led_state;
    digitalWrite(led_pin, led_state ? HIGH : LOW);

    // Send LED state to the queue
    xQueueSend(xQueue, &led_state, portMAX_DELAY);

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Task: print LED state when received
void waiting_for_state(void *parameter) {
  bool received_state;

  while (1) {
    if (xQueueReceive(xQueue, &received_state, portMAX_DELAY) == pdTRUE) {
      if (received_state)
        Serial.printf("[%lu ms] LED is ON\n", millis());
      else
        Serial.printf("[%lu ms] LED is OFF\n", millis());
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);

  // Create queue AFTER RTOS is ready
  xQueue = xQueueCreate(10, sizeof(bool));

  if (xQueue == NULL) {
    Serial.println("Error: Failed to create queue!");
    while (1);
  }

  // Create tasks
  xTaskCreatePinnedToCore(
      toggleLED,
      "Toggle LED",
      2048,
      NULL,
      1,
      NULL,
      app_cpu);

  xTaskCreatePinnedToCore(
      waiting_for_state,
      "Wait for LED State",
      2048,
      NULL,
      1,
      NULL,
      app_cpu);
}

void loop() {
  // nothing here
}
