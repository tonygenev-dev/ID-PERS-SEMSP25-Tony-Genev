#include "CANSender.h"
#include "UART.h"
#include <SPI.h>

static constexpr uint8_t CAN_CS_PIN = 10;

static MCP_CAN CAN0(CAN_CS_PIN);

void canInit() {
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
        uartLog("MCP2515 initialized successfully");
    } else {
        uartLog("Error initializing MCP2515");
    }

    CAN0.setMode(MCP_NORMAL);
}

void sendToDeviceA(uint8_t payload) {
    uint8_t data[1] = { payload };
    byte res = CAN0.sendMsgBuf(CAN_ID_DEVICE_A, 0, 1, data);

    if (res == CAN_OK) {
        uartLogHex("Sent to Device A payload: 0x", payload);
    } else {
        uartLog("Error sending to Device A");
    }
}

void sendToDeviceB(uint8_t payload) {
    uint8_t data[1] = { payload };
    byte res = CAN0.sendMsgBuf(CAN_ID_DEVICE_B, 0, 1, data);

    if (res == CAN_OK) {
        uartLogHex("Sent to Device B payload: 0x", payload);
    } else {
        uartLog("Error sending to Device B");
    }
}
