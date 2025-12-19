#include "BlinkControl.h"

static uint8_t leftLED;
static uint8_t rightLED;

static bool blinkLeft  = false;
static bool blinkRight = false;
static bool leftState  = false;
static bool rightState = false;

const int lastToggle = 0;
const int BLINK_MS = 500;

void blinkInit(uint8_t leftPin, uint8_t rightPin) {
    leftLED = leftPin;
    rightLED = rightPin;

    pinMode(leftLED, OUTPUT);
    pinMode(rightLED, OUTPUT);

    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
}

void setBlinkMode(BlinkCommand cmd) {
    blinkLeft = blinkRight = false;
    leftState = rightState = false;

    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);

    switch (cmd) {
        case BLINK_LEFT:
            blinkLeft = true;
            break;

        case BLINK_RIGHT:
            blinkRight = true;
            break;

        case BLINK_STOP:
        default:
            break;
    }
}

void updateBlink() {
    unsigned long now = millis();
    if ((blinkLeft || blinkRight) && (now - lastToggle >= BLINK_MS)) {
        lastToggle = now;

        if (blinkLeft) {
            leftState = !leftState;
            digitalWrite(leftLED, leftState ? HIGH : LOW);
            digitalWrite(rightLED, LOW);
        }
        else if (blinkRight) {
            rightState = !rightState;
            digitalWrite(rightLED, rightState ? HIGH : LOW);
            digitalWrite(leftLED, LOW);
        }
    }
}
