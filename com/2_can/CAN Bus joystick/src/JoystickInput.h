#pragma once
#include <Arduino.h>
#include <SparkFun_Qwiic_Joystick_Arduino_Library.h>
#include <Wire.h>
#include "DirectionLogic.h"

void joystickInit();
Direction readJoystickDirection(int& x, int& y);
