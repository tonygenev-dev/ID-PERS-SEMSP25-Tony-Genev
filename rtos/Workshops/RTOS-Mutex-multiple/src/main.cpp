#include <Arduino.h>

int counterRace = 0;     // shared counter WITHOUT mutex
int counterSafe = 0;     // shared counter WITH mutex
SemaphoreHandle_t counterMutex;

// Task with race condition
void taskRace(void *parameter) {
  while (1) {
    int temp = counterRace;          // read
    vTaskDelay(random(1, 5) / portTICK_PERIOD_MS);  // simulate some work
    counterRace = temp + 1;          // write
  }
}

// Task with mutex protection
void taskSafe(void *parameter) {
  while (1) {
    xSemaphoreTake(counterMutex, portMAX_DELAY); // lock
    counterSafe++;
    xSemaphoreGive(counterMutex);               // unlock
    vTaskDelay(random(1, 5) / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  counterMutex = xSemaphoreCreateMutex();
  if (counterMutex == NULL) {
    Serial.println("Failed to create mutex");
    while (1);
  }

  // Race condition tasks on separate cores
  xTaskCreatePinnedToCore(taskRace, "TaskRace1", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(taskRace, "TaskRace2", 2048, NULL, 1, NULL, 1);

  // Mutex-protected tasks on separate cores
  xTaskCreatePinnedToCore(taskSafe, "TaskSafe1", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(taskSafe, "TaskSafe2", 2048, NULL, 1, NULL, 1);
}

void loop() {
  Serial.printf("Race Counter: %d, Safe Counter: %d\n", counterRace, counterSafe);
  delay(500);  
}
