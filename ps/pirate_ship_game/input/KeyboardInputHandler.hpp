#pragma once
#include "IInputHandler.hpp"
#include <ftxui/component/event.hpp>

class KeyboardInputHandler : public IInputHandler {
public:
    GameDirection readInput() override {
        // This is a bit tricky because FTXUI is event-driven.
        // In a real game loop, we might poll or have the event loop feed this.
        // For now, we'll assume this is used in a context where we can check the last event
        // or we might need to change how we integrate with FTXUI.
        // However, adhering to the interface:
        return GameDirection::None; 
    }
    
    // Helper to convert FTXUI event to Direction
    GameDirection convertEvent(ftxui::Event event) {
        if (event == ftxui::Event::ArrowUp) return GameDirection::Up;
        if (event == ftxui::Event::ArrowDown) return GameDirection::Down;
        if (event == ftxui::Event::ArrowLeft) return GameDirection::Left;
        if (event == ftxui::Event::ArrowRight) return GameDirection::Right;
        return GameDirection::None;
    }

    bool isRestartPressed() override {
        return false; // Implement if we have a key for this
    }

    bool isQuitPressed() override {
        return false;
    }
};
