#include "Scenes.h"

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Scenes definition
Step scene1Steps[] = {
    {0, DELAY_FOR_SPRINKLER},
    {1, DELAY_FOR_SPRINKLER}
};

Step scene2Steps[] = {
    {4, DELAY_FOR_SPRINKLER}
};

Step scene3Steps[] = {
    {3, DELAY_FOR_SPRINKLER},
    {1, DELAY_FOR_SPRINKLER}
};

Scene scenes[] = {
    {scene1Steps, sizeof(scene1Steps) / sizeof(Step)},
    {scene2Steps, sizeof(scene2Steps) / sizeof(Step)},
    {scene3Steps, sizeof(scene3Steps) / sizeof(Step)}
};

const int NUM_SCENES = sizeof(scenes) / sizeof(Scene);


// Start a scene task
void executeScene(void* param) {
    Scene* scene = (Scene*)param;

    Serial.println("Scene started with " + String(scene->stepCount) + " steps");

    for (int i = 0; i < scene->stepCount; i++) {
        activateSprinkler(scene->steps[i].sprinklerIndex,
                          scene->steps[i].durationMs);
    }

    Serial.println("Scene finished");
    vTaskDelete(NULL);
}


// Create a task to run the scene
void startScene(int sceneIndex) {
    if (sceneIndex < 0 || sceneIndex >= NUM_SCENES) {
        Serial.println("Invalid scene index");
        return;
    }

    xTaskCreatePinnedToCore(
        executeScene,
        "SceneTask",
        4096,
        &scenes[sceneIndex],
        1,
        NULL,
        app_cpu
    );
}
