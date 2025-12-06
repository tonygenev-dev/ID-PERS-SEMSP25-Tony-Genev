#include <Arduino.h>
#include "Scenes.h"

void initUART() {
    Serial.begin(115200);
    Serial.println("System ready. Send 1, 2, or 3 to start a scene.");
}

void handleUART() {
    if (!Serial.available()) return;

    char c = Serial.read();

    if (c >= '1' && c <= '3') {
        startScene(c - '1');
    } else {
        Serial.println("Unknown scene number");
    }
}
