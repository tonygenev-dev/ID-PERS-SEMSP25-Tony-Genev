#include <Arduino.h>

// Use 2 cores for now
static const BaseType_t app_cpu = 0;
static const BaseType_t app_cpu2 = 1;

int counter = 0; // shared variable

void task1(void *parameter){
  while(1){
    int temp = counter;
    vTaskDelay(random(1, 5) / portTICK_PERIOD_MS);
    counter = temp + 1;
  }
}

void task2(void *parameter){
  while(1){
    int temp = counter;
    vTaskDelay(random(1, 5) / portTICK_PERIOD_MS);
    counter = temp + 1;
  }
}

void setup(){
  Serial.begin(115200);
  xTaskCreatePinnedToCore(
                      task1,
                      "Task 1",
                      2048,
                      NULL,
                      1,
                      NULL,
                      app_cpu); // Core 0
  xTaskCreatePinnedToCore(
                      task2,
                      "Task 2",
                      2048,
                      NULL,
                      1,
                      NULL,
                      app_cpu2); // Core 1
}

void loop(){
  Serial.printf("Counter: %d\n", counter);
  delay(500);
}
