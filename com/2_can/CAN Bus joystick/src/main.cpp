#include <Arduino.h>
#include "UART.h"
#include "JoystickInput.h"
#include "CANSender.h"
#include "DirectionLogic.h"

const int STABLE_MS = 50;
const int PRINT_MS  = 200;

static Direction lastDirection = DIR_CENTER;
static unsigned long lastPrint = 0;

void setup() {
    uartInit(115200);
    joystickInit();
    canInit();

    uartLog("Joystick CAN sender ready");
}

void loop() {
    int x, y;
    Direction dir = readJoystickDirection(x, y);

    unsigned long now = millis();

    if (now - lastPrint >= PRINT_MS) {
        Serial.print("X=");
        Serial.print(x);
        Serial.print(" Y=");
        Serial.print(y);
        Serial.print(" -> ");
        Serial.println(directionName(dir));
        lastPrint = now;
    }

    if (dir != lastDirection) {
        unsigned long t0 = millis();
        while (millis() - t0 < STABLE_MS) delay(5);

        int x2, y2;
        Direction confirmed = readJoystickDirection(x2, y2);

        if (confirmed == dir) {
            switch (dir) {
                case DIR_LEFT:   sendToDeviceA(0x01); break;
                case DIR_RIGHT:  sendToDeviceA(0x02); break;
                case DIR_CENTER: sendToDeviceA(0x00); break;
                case DIR_UP:     sendToDeviceB(0x01); break;
                case DIR_DOWN:   sendToDeviceB(0x00); break;
                default: break;
            }
            lastDirection = dir;
        }
    }

    delay(10);
}
