#include <Arduino.h>

// Use only core 1
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Define sprinkler pins
#define SPRINKLER1_PIN LED_BUILTIN
#define SPRINKLER2_PIN 13
#define SPRINKLER3_PIN 14
#define SPRINKLER4_PIN 27
#define SPRINKLER5_PIN 26
#define SPRINKLER6_PIN 25
#define SPRINKLER7_PIN 33
#define SPRINKLER8_PIN 32

// Enum for groups
enum Group {
  GROUP_A,
  GROUP_B,
  NUM_GROUPS // Total number of groups
};

// Sprinkler struct
struct Sprinkler {
  int pin;
  Group group;
};

// Sprinkler array
Sprinkler sprinklers[] = {
  {SPRINKLER1_PIN, GROUP_A},
  {SPRINKLER2_PIN, GROUP_A},
  {SPRINKLER3_PIN, GROUP_A},
  {SPRINKLER4_PIN, GROUP_A},
  {SPRINKLER5_PIN, GROUP_B},
  {SPRINKLER6_PIN, GROUP_B},
  {SPRINKLER7_PIN, GROUP_B},
  {SPRINKLER8_PIN, GROUP_B}
};

// The number of sprinklers
const int NUM_SPRINKLERS = sizeof(sprinklers) / sizeof(sprinklers[0]);
const int NUM_SCENES = 3;

// Mutexes for sprinklers and groups
SemaphoreHandle_t sprinklerMutex[NUM_SPRINKLERS];
SemaphoreHandle_t groupMutex[NUM_GROUPS];
SemaphoreHandle_t sceneMutex[NUM_SCENES];


// Activate sprinkler function
void activateSprinkler(int index, int duration_ms) {
  int groupIndex = sprinklers[index].group;

  // Take group mutex first, then sprinkler mutex
  xSemaphoreTake(groupMutex[groupIndex], portMAX_DELAY);
  xSemaphoreTake(sprinklerMutex[index], portMAX_DELAY);

  // Activate sprinkler
  Serial.println("Activating Sprinkler on pin "+ String(sprinklers[index].pin) + String(sprinklers[index].group == GROUP_A ? " (Group A)" : " (Group B)"));
  digitalWrite(sprinklers[index].pin, HIGH);
  vTaskDelay(duration_ms / portTICK_PERIOD_MS);
  digitalWrite(sprinklers[index].pin, LOW);
  Serial.println("Deactivating Sprinkler on pin "+ String(sprinklers[index].pin));


  // Release mutexes
  xSemaphoreGive(sprinklerMutex[index]);
  xSemaphoreGive(groupMutex[groupIndex]);
}

// Scenes
void scene1(void *parameter) {
  xSemaphoreTake(sceneMutex[0], portMAX_DELAY);
  Serial.println("Scene 1 started");
  activateSprinkler(0, 5000); // Sprinkler 1
  activateSprinkler(1, 5000); // Sprinkler 2
  Serial.println("Scene 1 finished");
  xSemaphoreGive(sceneMutex[0]);
  vTaskDelete(NULL);
}

void scene2(void *parameter) {
  xSemaphoreTake(sceneMutex[1], portMAX_DELAY);
  Serial.println("Scene 2 started");
  activateSprinkler(4, 5000); // Sprinkler 3
  Serial.println("Scene 2 finished");
  xSemaphoreGive(sceneMutex[1]);
  vTaskDelete(NULL);
}

void scene3(void *parameter) {
  xSemaphoreTake(sceneMutex[2], portMAX_DELAY);
  Serial.println("Scene 3 started");
  activateSprinkler(3, 5000); // Sprinkler 4
  activateSprinkler(1, 5000); // Sprinkler 2
  Serial.println("Scene 3 finished");
  xSemaphoreGive(sceneMutex[2]);
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);
  Serial.println("System ready. Send 1, 2, or 3 to start a Scene.");

  // Initialize pins and sprinkler mutexes
  for (int i = 0; i < NUM_SPRINKLERS; i++) {
    pinMode(sprinklers[i].pin, OUTPUT);
    digitalWrite(sprinklers[i].pin, LOW);
    sprinklerMutex[i] = xSemaphoreCreateMutex();
  }

  // Initialize group mutexes
  for (int g = 0; g < NUM_GROUPS; g++) {
    groupMutex[g] = xSemaphoreCreateMutex();
  }

  // Initialize scene mutexes
  for (int s = 0; s < NUM_SCENES; s++) {
    sceneMutex[s] = xSemaphoreCreateMutex();
  }
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
