#ifndef SPRINKLER_H
#define SPRINKLER_H

#include <Arduino.h>

//Definitions
#define SPRINKLER1_PIN LED_BUILTIN
#define SPRINKLER2_PIN 13
#define SPRINKLER3_PIN 14
#define SPRINKLER4_PIN 27
#define SPRINKLER5_PIN 26
#define SPRINKLER6_PIN 25
#define SPRINKLER7_PIN 33
#define SPRINKLER8_PIN 32

#define DELAY_FOR_SPRINKLER 5000

//Structures
enum Group {
    GROUP_A,
    GROUP_B,
    NUM_GROUPS
};

struct Sprinkler {
    int pin;
    Group group;
};


extern Sprinkler sprinklers[];
extern const int NUM_SPRINKLERS;

extern SemaphoreHandle_t sprinklerMutex[];
extern SemaphoreHandle_t groupMutex[];

// Function
void activateSprinkler(int index, int durationMs);

#endif
