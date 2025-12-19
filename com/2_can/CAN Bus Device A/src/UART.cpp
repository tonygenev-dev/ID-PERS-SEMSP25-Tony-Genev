#include "UART.h"

void uartInit(unsigned long baudrate) {
    Serial.begin(baudrate);
    while (!Serial) { delay(5); }
}

void uartLog(const char* message) {
    Serial.println(message);
}
