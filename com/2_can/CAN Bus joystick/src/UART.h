#pragma once
#include <Arduino.h>

void uartInit(unsigned long baudrate);
void uartLog(const char* msg);
void uartLogHex(const char* prefix, uint32_t value);
