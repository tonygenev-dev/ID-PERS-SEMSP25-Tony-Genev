#include "DirectionLogic.h"

const int THRESHOLD_LOW  = 250;
const int THRESHOLD_HIGH = 775;

const char* directionName(Direction d) {
    switch (d) {
        case DIR_LEFT:   return "LEFT";
        case DIR_RIGHT:  return "RIGHT";
        case DIR_CENTER: return "CENTER";
        case DIR_UP:     return "UP";
        case DIR_DOWN:   return "DOWN";
        default:         return "UNKNOWN";
    }
}

Direction mapToDirection(int x, int y) {
    if (x > THRESHOLD_HIGH) return DIR_UP;
    if (x < THRESHOLD_LOW)  return DIR_DOWN;
    if (y > THRESHOLD_HIGH) return DIR_RIGHT;
    if (y < THRESHOLD_LOW)  return DIR_LEFT;
    return DIR_CENTER;
}
