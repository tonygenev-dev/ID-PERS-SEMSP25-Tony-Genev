// Device A: controls left/right blink (File: src/main.cpp)
#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

#define CAN0_INT 2
MCP_CAN CAN0(10);

const uint32_t CAN_ID_DEVICE_A = 0x101;

const uint8_t LED_LEFT_PIN  = 7;
const uint8_t LED_RIGHT_PIN = 8;

unsigned long lastToggle = 0;
const unsigned long BLINK_MS = 500;

bool blinkLeft = false;
bool blinkRight = false;
bool leftState = false;
bool rightState = false;

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
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  digitalWrite(LED_LEFT_PIN, LOW);
  digitalWrite(LED_RIGHT_PIN, LOW);
  Serial.println("Device A ready.");
}

void handleMsg() {
  CAN0.readMsgBuf(&rxId, &len, rxBuf);
  if (rxId == CAN_ID_DEVICE_A && len >= 1) {
    uint8_t cmd = rxBuf[0];
    if (cmd == 0x01) { // LEFT
      Serial.println("CMD LEFT (blink left)");
      blinkLeft = true; blinkRight = false;
      leftState = false;
      digitalWrite(LED_RIGHT_PIN, LOW);
    } else if (cmd == 0x02) { // RIGHT
      Serial.println("CMD RIGHT (blink right)");
      blinkRight = true; blinkLeft = false;
      rightState = false;
      digitalWrite(LED_LEFT_PIN, LOW);
    } else if (cmd == 0x00) { // CENTER -> stop
      Serial.println("CMD CENTER (stop)");
      blinkLeft = blinkRight = false;
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(LED_RIGHT_PIN, LOW);
    }
  }
}

void loop() {
  if (!digitalRead(CAN0_INT)) handleMsg();

  unsigned long now = millis();
  if ((blinkLeft || blinkRight) && (now - lastToggle >= BLINK_MS)) {
    lastToggle = now;
    if (blinkLeft) {
      leftState = !leftState;
      digitalWrite(LED_LEFT_PIN, leftState ? HIGH : LOW);
      digitalWrite(LED_RIGHT_PIN, LOW);
    } else if (blinkRight) {
      rightState = !rightState;
      digitalWrite(LED_RIGHT_PIN, rightState ? HIGH : LOW);
      digitalWrite(LED_LEFT_PIN, LOW);
    }
  }
  delay(5);
}