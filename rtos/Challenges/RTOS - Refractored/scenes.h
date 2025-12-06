#ifndef SCENES_H
#define SCENES_H

#include <Arduino.h>
#include "Sprinkler.h"

//Scene structures
struct Step {
    int sprinklerIndex;
    int durationMs;
};

struct Scene {
    Step* steps;
    int stepCount;
};

// Globals declared in .cpp
extern Scene scenes[];
extern const int NUM_SCENES;

// Functions
void startScene(int sceneIndex);
void executeScene(void* param);

#endif
