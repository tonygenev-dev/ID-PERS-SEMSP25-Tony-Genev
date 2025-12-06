#include "Sprinkler.h"

// Sprinkler list with groups
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

const int NUM_SPRINKLERS = sizeof(sprinklers) / sizeof(sprinklers[0]);

SemaphoreHandle_t sprinklerMutex[8];
SemaphoreHandle_t groupMutex[NUM_GROUPS];


//Activation function
void activateSprinkler(int index, int durationMs) {
    int groupIndex = sprinklers[index].group;

    xSemaphoreTake(groupMutex[groupIndex], portMAX_DELAY);
    xSemaphoreTake(sprinklerMutex[index], portMAX_DELAY);

    Serial.println("Activating Sprinkler " + String(index + 1));
    digitalWrite(sprinklers[index].pin, HIGH);

    vTaskDelay(durationMs / portTICK_PERIOD_MS);

    digitalWrite(sprinklers[index].pin, LOW);
    Serial.println("Deactivating Sprinkler " + String(index + 1));

    xSemaphoreGive(sprinklerMutex[index]);
    xSemaphoreGive(groupMutex[groupIndex]);
}
