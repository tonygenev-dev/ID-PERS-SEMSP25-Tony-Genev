#pragma once

enum class GameDirection {
    None,
    Up,
    Down,
    Left,
    Right
};

class IInputHandler {
public:
    virtual ~IInputHandler() = default;
    virtual GameDirection readInput() = 0;
    virtual bool isRestartPressed() = 0;
    virtual bool isQuitPressed() = 0;
};
