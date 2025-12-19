#pragma once
#include <Arduino.h>
#include <mcp_can.h>

const int CAN_ID_DEVICE_A = 0x101;
const int CAN_ID_DEVICE_B = 0x102;

void canInit();
void sendToDeviceA(uint8_t payload);
void sendToDeviceB(uint8_t payload);
