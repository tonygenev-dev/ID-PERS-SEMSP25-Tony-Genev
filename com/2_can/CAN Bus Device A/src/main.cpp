#include <Arduino.h>
#include "UART.h"
#include "CANHandler.h"
#include "BlinkControl.h"

const int LED_LEFT_PIN  = 7;
const int LED_RIGHT_PIN = 8;

void setup() {
    uartInit(115200);
    blinkInit(LED_LEFT_PIN, LED_RIGHT_PIN);
    canInit();

    uartLog("Device A ready");
}

void loop() {
    handleCANMessage();
    updateBlink();
    delay(5);
}
