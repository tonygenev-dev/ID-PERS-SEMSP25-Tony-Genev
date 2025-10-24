#include <Arduino.h>

// Use only core 1
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Sprinkler pins
#define SPRINKLER1_PIN LED_BUILTIN
#define SPRINKLER2_PIN 13
#define SPRINKLER3_PIN 14
#define SPRINKLER4_PIN 27
#define SPRINKLER5_PIN 26
#define SPRINKLER6_PIN 25
#define SPRINKLER7_PIN 33
#define SPRINKLER8_PIN 32

enum Group { GROUP_A, GROUP_B, NUM_GROUPS };

struct Sprinkler { int pin; Group group; };

// Sprinklers
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

const int NUM_SPRINKLERS = sizeof(sprinklers)/sizeof(sprinklers[0]);
const int NUM_SCENES = 3;

// Mutexes
SemaphoreHandle_t sprinklerMutex[NUM_SPRINKLERS];
SemaphoreHandle_t groupMutex[NUM_GROUPS];
SemaphoreHandle_t sceneMutex[NUM_SCENES];

// Step structure
struct Step {
  int sprinklerIndex;
  int durationMs;
};

// Activate sprinkler
void activateSprinkler(int index, int duration_ms) {
  int groupIndex = sprinklers[index].group;
  xSemaphoreTake(groupMutex[groupIndex], portMAX_DELAY);
  xSemaphoreTake(sprinklerMutex[index], portMAX_DELAY);

  Serial.println("Activating Sprinkler " + String(index+1));
  digitalWrite(sprinklers[index].pin, HIGH);
  vTaskDelay(duration_ms / portTICK_PERIOD_MS);
  digitalWrite(sprinklers[index].pin, LOW);
  Serial.println("Deactivating Sprinkler " + String(index+1));

  xSemaphoreGive(sprinklerMutex[index]);
  xSemaphoreGive(groupMutex[groupIndex]);
}

// Scene execution function
void executeScene(void* param) {
  QueueHandle_t queue = (QueueHandle_t)param;
  Step step;

  while(xQueueReceive(queue, &step, portMAX_DELAY) == pdTRUE) {
    activateSprinkler(step.sprinklerIndex, step.durationMs);
  }

  vQueueDelete(queue); // delete the queue after use
  vTaskDelete(NULL);
}

// Start a scene by creating a queue and copying its steps
void startScene(int sceneNumber) {
  Step steps[2]; 
  if(sceneNumber == 1){ steps[0]={0,5000}; steps[1]={1,5000}; }
  if(sceneNumber == 2){ steps[0]={4,5000}; }
  if(sceneNumber == 3){ steps[0]={3,5000}; steps[1]={1,5000}; }

  // Create queue and copy steps
  QueueHandle_t queue = xQueueCreate(sizeof(steps)/sizeof(steps[0]), sizeof(Step));
  for(int i=0;i<sizeof(steps)/sizeof(steps[0]);i++){
    xQueueSend(queue, &steps[i], 0);
  }

  // Start Scene task
  xTaskCreatePinnedToCore(executeScene, "SceneTask", 4096, queue, 1, NULL, app_cpu);
}

void setup() {
  Serial.begin(115200);
  for(int i=0;i<NUM_SPRINKLERS;i++){
    pinMode(sprinklers[i].pin, OUTPUT);
    digitalWrite(sprinklers[i].pin, LOW);
    sprinklerMutex[i]=xSemaphoreCreateMutex();
  }
  for(int g=0;g<NUM_GROUPS;g++) groupMutex[g]=xSemaphoreCreateMutex();
  for(int s=0;s<NUM_SCENES;s++) sceneMutex[s]=xSemaphoreCreateMutex();

  Serial.println("System ready. Send 1, 2, or 3 to start a Scene.");
}

void loop() {
  if(Serial.available()){
    char c = Serial.read();
    switch(c){
      case '1': startScene(1); break;
      case '2': startScene(2); break;
      case '3': startScene(3); break;
    }
  }
}
