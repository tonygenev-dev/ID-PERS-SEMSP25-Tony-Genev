#pragma once
#include "KeyboardInputHandler.hpp"
#include <ftxui/component/event.hpp>

// Adapter to bridge FTXUI events to our InputHandler
class FTXUIInputAdapter : public KeyboardInputHandler {
    GameDirection currentDirection = GameDirection::None;
    bool quit = false;
public:
    void SetLastEvent(ftxui::Event event) {
        currentDirection = convertEvent(event);
        if (event == ftxui::Event::Character('q')) {
            quit = true;
        }
    }

    GameDirection readInput() override {
        GameDirection d = currentDirection;
        currentDirection = GameDirection::None; // Consume
        return d;
    }

    bool isQuitPressed() override {
        return quit;
    }
    
    void Reset() {
        quit = false;
        currentDirection = GameDirection::None;
    }
};
