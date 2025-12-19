#pragma once
#include <Arduino.h>
#include <mcp_can.h>

constexpr uint32_t CAN_ID_DEVICE_A = 0x101;

void canInit();
void handleCANMessage();
