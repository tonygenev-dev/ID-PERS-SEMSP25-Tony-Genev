#include "JoystickInput.h"
#include "UART.h"

const int JOYSTICK_ADDR = 0x34;
static JOYSTICK joystick;

void joystickInit() {
    Wire.begin();

    if (!joystick.begin(Wire, JOYSTICK_ADDR)) {
        uartLog("Joystick not found. Check wiring.");
        while (1);
    }

    uartLog("Joystick initialized");
}

Direction readJoystickDirection(int& x, int& y) {
    x = joystick.getHorizontal();
    y = joystick.getVertical();
    return mapToDirection(x, y);
}
