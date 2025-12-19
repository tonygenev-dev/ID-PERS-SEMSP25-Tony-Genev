#pragma once
#include <Arduino.h>
#include <mcp_can.h>

constexpr uint32_t CAN_ID_DEVICE_B = 0x102;

void canInit();
void handleCANMessage();
