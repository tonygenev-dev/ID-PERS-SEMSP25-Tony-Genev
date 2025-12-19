#include "CANHandler.h"
#include "BlinkControl.h"
#include "UART.h"
#include <SPI.h>

constexpr uint8_t CAN_CS_PIN  = 10;
constexpr uint8_t CAN_INT_PIN = 2;

static MCP_CAN CAN0(CAN_CS_PIN);

static uint32_t rxId;
static uint8_t  rxLen;
static uint8_t  rxBuf[8];

void canInit() {
    pinMode(CAN_INT_PIN, INPUT);

    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
        uartLog("MCP2515 initialized successfully");
    } else {
        uartLog("Error initializing MCP2515");
    }

    CAN0.setMode(MCP_NORMAL);
}

void handleCANMessage() {
    if (digitalRead(CAN_INT_PIN)) return;

    CAN0.readMsgBuf(&rxId, &rxLen, rxBuf);

    if (rxId != CAN_ID_DEVICE_A || rxLen < 1) return;

    switch (rxBuf[0]) {
        case BLINK_LEFT:
            uartLog("CMD LEFT");
            setBlinkMode(BLINK_LEFT);
            break;

        case BLINK_RIGHT:
            uartLog("CMD RIGHT");
            setBlinkMode(BLINK_RIGHT);
            break;

        case BLINK_STOP:
            uartLog("CMD CENTER / STOP");
            setBlinkMode(BLINK_STOP);
            break;

        default:
            uartLog("Unknown CAN command");
            break;
    }
}
