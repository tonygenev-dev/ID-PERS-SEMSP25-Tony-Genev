#pragma once
#include <memory>
#include <string>
#include <vector>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp> // Added for Canvas
#include "GameEngine.hpp"
#include "ScoreManager.hpp"
#include "FTXUIInputAdapter.hpp"

enum class AppState {
    MENU,
    NAME_INPUT,
    GAME,
    LEADERBOARD
};

#include <thread>
#include <atomic>
#include <chrono>
#include <cmath> // For sin()

#include <thread>
#include <atomic>
#include <chrono>

class GameApplication {
public:
    GameApplication();
    ~GameApplication(); // Added destructor declaration
    void Run();

private:
    // State
    AppState currentState;
    std::string playerName;
    ScoreManager scoreManager;
    
    // Game Engine
    std::shared_ptr<FTXUIInputAdapter> inputAdapter;
    std::unique_ptr<GameEngine> game;
    int obstacle_spawn_counter;

    // UI Components
    ftxui::ScreenInteractive screen;
    int menu_selected;
    std::vector<std::string> menu_entries;
    ftxui::Component menu;
    ftxui::Component name_input;
    
    // Helpers
    void SetupComponents();
    ftxui::Element RenderLeaderboard();
    ftxui::Element RenderMenu(); // New method
    ftxui::Element RenderMain();
    bool OnEvent(ftxui::Event event);
    
    // Animation
    std::thread animationThread;
    std::atomic<bool> isRunning;
    std::atomic<bool> animationFramePending; // Flow control
    void AnimationLoop();
};
