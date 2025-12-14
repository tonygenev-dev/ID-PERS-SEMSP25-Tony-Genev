// Device B: high-beam on/off (File: src/main.cpp)
#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

#define CAN0_INT 2
MCP_CAN CAN0(10);

const uint32_t CAN_ID_DEVICE_B = 0x102;
const uint8_t LED_HIGH_PIN = 7;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(5); }

  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");
  CAN0.setMode(MCP_NORMAL);

  pinMode(CAN0_INT, INPUT);
  pinMode(LED_HIGH_PIN, OUTPUT);
  digitalWrite(LED_HIGH_PIN, LOW);
  Serial.println("Device B ready.");
}

void loop() {
  if (!digitalRead(CAN0_INT)) {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);
    if (rxId == CAN_ID_DEVICE_B && len >= 1) {
      uint8_t cmd = rxBuf[0];
      if (cmd == 0x01) {
        Serial.println("HIGH ON");
        digitalWrite(LED_HIGH_PIN, HIGH);
      } else if (cmd == 0x00) {
        Serial.println("HIGH OFF");
        digitalWrite(LED_HIGH_PIN, LOW);
      }
    }
  }
  delay(5);
}