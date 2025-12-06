#include <Arduino.h>
#include "Sprinkler.h"
#include "Scenes.h"
#include "UARTHandler.cpp"

void setup() {
    initUART();

    // Initialize sprinkler pins + mutexes
    for (int i = 0; i < NUM_SPRINKLERS; i++) {
        pinMode(sprinklers[i].pin, OUTPUT);
        digitalWrite(sprinklers[i].pin, LOW);
        sprinklerMutex[i] = xSemaphoreCreateMutex();
    }

    // Group mutexes
    for (int g = 0; g < NUM_GROUPS; g++) {
        groupMutex[g] = xSemaphoreCreateMutex();
    }
}

void loop() {
    handleUART();   
}
