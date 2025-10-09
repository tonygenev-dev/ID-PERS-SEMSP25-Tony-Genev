#include <Arduino.h>

// Use only core 1 for now
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Sprinkler pins
static const int sprinkler1 = 12;
static const int sprinkler2 = 13;
static const int sprinkler3 = 14;
static const int sprinkler4 = 27;
static const int sprinkler5 = 26;

// Scene 1: Sprinklers 1 & 2
void scene1(void *parameter) {
  Serial.println("Scene 1 started");
  digitalWrite(sprinkler1, HIGH);
  vTaskDelay(5000 / portTICK_PERIOD_MS); // 5 seconds for testing
  digitalWrite(sprinkler1, LOW);

  digitalWrite(sprinkler2, HIGH);
  vTaskDelay(5000 / portTICK_PERIOD_MS);
  digitalWrite(sprinkler2, LOW);

  Serial.println("Scene 1 finished");
  vTaskDelete(NULL);
}

// Scene 2: Sprinkler 3
void scene2(void *parameter) {
  Serial.println("Scene 2 started");
  digitalWrite(sprinkler3, HIGH);
  vTaskDelay(5000 / portTICK_PERIOD_MS);
  digitalWrite(sprinkler3, LOW);
  Serial.println("Scene 2 finished");

  vTaskDelete(NULL);
}

// Scene 3: Sprinklers 4 & 5
void scene3(void *parameter) {
  Serial.println("Scene 3 started");
  digitalWrite(sprinkler4, HIGH);
  digitalWrite(sprinkler5, HIGH);
  vTaskDelay(5000 / portTICK_PERIOD_MS);
  digitalWrite(sprinkler4, LOW);
  digitalWrite(sprinkler5, LOW);
  Serial.println("Scene 3 finished");

  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);

  // Initialize sprinkler pins
  pinMode(sprinkler1, OUTPUT);
  pinMode(sprinkler2, OUTPUT);
  pinMode(sprinkler3, OUTPUT);
  pinMode(sprinkler4, OUTPUT);
  pinMode(sprinkler5, OUTPUT);

  digitalWrite(sprinkler1, LOW);
  digitalWrite(sprinkler2, LOW);
  digitalWrite(sprinkler3, LOW);
  digitalWrite(sprinkler4, LOW);
  digitalWrite(sprinkler5, LOW);

  Serial.println("System ready. Send 1, 2, or 3 to start a Scene.");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();

    switch (c) {
      case '1':
        xTaskCreatePinnedToCore(scene1, "Scene 1", 4096, NULL, 1, NULL, app_cpu);
        break;
      case '2':
        xTaskCreatePinnedToCore(scene2, "Scene 2", 4096, NULL, 1, NULL, app_cpu);
        break;
      case '3':
        xTaskCreatePinnedToCore(scene3, "Scene 3", 4096, NULL, 1, NULL, app_cpu);
        break;
      default:
        Serial.println("Unknown scene number");
        break;
    }
  }
}
