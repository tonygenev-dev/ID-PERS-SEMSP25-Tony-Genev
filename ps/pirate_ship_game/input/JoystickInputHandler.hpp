#pragma once
#include "IInputHandler.hpp"

class JoystickInputHandler : public IInputHandler {
public:
    GameDirection readInput() override {
        // Mock implementation for Joystick
        return GameDirection::None;
    }

    bool isRestartPressed() override {
        return false;
    }

    bool isQuitPressed() override {
        return false;
    }
};
