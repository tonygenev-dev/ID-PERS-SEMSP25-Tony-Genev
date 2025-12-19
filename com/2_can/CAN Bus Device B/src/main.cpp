// Device B: high-beam on/off main.cpp
#include <Arduino.h>
#include "UART.h"
#include "CANHandler.h"
#include "BeamControl.h"

constexpr uint8_t HIGH_BEAM_LED_PIN = 7;

void setup() {
    uartInit(115200);
    beamInit(HIGH_BEAM_LED_PIN);
    canInit();

    uartLog("Device B ready");
}

void loop() {
    handleCANMessage();
    delay(5);
}
