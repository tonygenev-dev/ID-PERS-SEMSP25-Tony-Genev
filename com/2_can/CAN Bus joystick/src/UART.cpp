#include "UART.h"

void uartInit(unsigned long baudrate) {
    Serial.begin(baudrate);
    while (!Serial) { delay(5); }
}

void uartLog(const char* msg) {
    Serial.println(msg);
}

void uartLogHex(const char* prefix, uint32_t value) {
    Serial.print(prefix);
    Serial.println(value, HEX);
}
