#pragma once
#include <Arduino.h>

enum BlinkCommand : uint8_t {
    BLINK_STOP  = 0x00,
    BLINK_LEFT  = 0x01,
    BLINK_RIGHT = 0x02
};

void blinkInit(uint8_t leftPin, uint8_t rightPin);
void setBlinkMode(BlinkCommand cmd);
void updateBlink();
