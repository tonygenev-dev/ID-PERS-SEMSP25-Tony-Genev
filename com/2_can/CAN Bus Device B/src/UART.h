#pragma once
#include <Arduino.h>

void uartInit(unsigned long baudrate);
void uartLog(const char* message);
