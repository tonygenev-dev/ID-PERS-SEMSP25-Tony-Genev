#include "CANHandler.h"
#include "BeamControl.h"
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

    if (rxId != CAN_ID_DEVICE_B || rxLen < 1) return;

    switch (rxBuf[0]) {
        case BEAM_ON:
            uartLog("HIGH ON");
            setBeamState(BEAM_ON);
            break;

        case BEAM_OFF:
            uartLog("HIGH OFF");
            setBeamState(BEAM_OFF);
            break;

        default:
            uartLog("Unknown CAN command");
            break;
    }
}
