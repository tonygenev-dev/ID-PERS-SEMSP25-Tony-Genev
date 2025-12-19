#pragma once
#include <Arduino.h>

enum Direction : uint8_t {
    DIR_LEFT   = 0x10,
    DIR_RIGHT  = 0x11,
    DIR_CENTER = 0x12,
    DIR_UP     = 0x13,
    DIR_DOWN   = 0x14
};

const char* directionName(Direction d);
Direction mapToDirection(int x, int y);
