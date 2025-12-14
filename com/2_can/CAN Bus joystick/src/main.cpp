#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <SparkFun_Qwiic_Joystick_Arduino_Library.h>
#include <Wire.h>

MCP_CAN CAN0(10);     // CS pin for MCP2515
uint8_t Address = 0x34; // I2C address for the joystick
JOYSTICK joystick;

// Message format:
// Device A (left/right blink) -> CAN ID 0x101
//   payload: 0x01 = LEFT, 0x02 = RIGHT, 0x00 = CENTER (stop)
// Device B (high-beam) -> CAN ID 0x102
//   payload: 0x01 = HIGH_ON, 0x00 = HIGH_OFF

const uint32_t CAN_ID_DEVICE_A = 0x101;
const uint32_t CAN_ID_DEVICE_B = 0x102;

const int THRESHOLD_LOW = 250;
const int THRESHOLD_HIGH = 775;
const unsigned long STABLE_MS = 50;
const unsigned long PRINT_MS = 200;

uint8_t lastDirection = 0xFF;
unsigned long lastPrint = 0;

const char* dirName(uint8_t d) {
  switch (d) {
    case 0x10: return "LEFT";
    case 0x11: return "RIGHT";
    case 0x12: return "CENTER";
    case 0x13: return "UP";
    case 0x14: return "DOWN";
  }
  return "UNK";
}

uint8_t mapToDirection(int x, int y) {
  if (x > THRESHOLD_HIGH) return 0x13; // UP
  if (x < THRESHOLD_LOW)  return 0x14; // DOWN
  if (y > THRESHOLD_HIGH) return 0x11; // RIGHT
  if (y < THRESHOLD_LOW)  return 0x10; // LEFT
  return 0x12; // CENTER
}

void sendToDeviceA(uint8_t payload) {
  uint8_t data[1] = { payload };
  byte res = CAN0.sendMsgBuf(CAN_ID_DEVICE_A, 0, 1, data);
  if (res == CAN_OK) {
    Serial.print("Sent to A (0x");
    Serial.print(CAN_ID_DEVICE_A, HEX);
    Serial.print("): 0x");
    Serial.println(payload, HEX);
  } else Serial.println("Error sending to A");
}

void sendToDeviceB(uint8_t payload) {
  uint8_t data[1] = { payload };
  byte res = CAN0.sendMsgBuf(CAN_ID_DEVICE_B, 0, 1, data);
  if (res == CAN_OK) {
    Serial.print("Sent to B (0x");
    Serial.print(CAN_ID_DEVICE_B, HEX);
    Serial.print("): 0x");
    Serial.println(payload, HEX);
  } else Serial.println("Error sending to B");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(5);

  Wire.begin();
  if (joystick.begin(Wire, Address) == false) {
    Serial.println("Joystick not found. Check wiring.");
    while (1);
  }

  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");
  CAN0.setMode(MCP_NORMAL);

  Serial.println("Joystick CAN sender ready.");
}

void loop() {
  int x = joystick.getHorizontal();
  int y = joystick.getVertical();
  uint8_t dir = mapToDirection(x, y);

  unsigned long now = millis();
  if (now - lastPrint >= PRINT_MS) {
    Serial.print("X=");
    Serial.print(x);
    Serial.print(" Y=");
    Serial.print(y);
    Serial.print(" -> ");
    Serial.println(dirName(dir));
    lastPrint = now;
  }

  if (dir != lastDirection) {
    // stability debounce
    unsigned long t0 = millis();
    while (millis() - t0 < STABLE_MS) delay(5);
    int x2 = joystick.getHorizontal();
    int y2 = joystick.getVertical();
    uint8_t confirmed = mapToDirection(x2, y2);
    if (confirmed == dir) {
      // Map the logical direction to the device-specific messages:
      if (dir == 0x10) { // LEFT
        sendToDeviceA(0x01);
      } else if (dir == 0x11) { // RIGHT
        sendToDeviceA(0x02);
      } else if (dir == 0x12) { // CENTER
        sendToDeviceA(0x00);
      } else if (dir == 0x13) { // UP
        sendToDeviceB(0x01);
      } else if (dir == 0x14) { // DOWN
        sendToDeviceB(0x00);
      }
      lastDirection = dir;
    }
  }

  delay(10);
}