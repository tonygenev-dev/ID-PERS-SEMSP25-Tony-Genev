#include "GameApplication.hpp"
#include "GameConstants.hpp"
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace ftxui;

const std::vector<std::string> SHIP_ART = {
    "      |    |    |",
    "     )_)  )_)  )_)",
    "    )___))___))___)\\",
    "   )____)____)_____)\\\\",
    " _____|____|____|____\\\\__",
    " \\__________________/",
};

GameApplication::GameApplication() 
    : screen(ScreenInteractive::Fullscreen()),
      currentState(AppState::MENU),
      obstacle_spawn_counter(0),
      menu_selected(0),
      isRunning(true),
      animationFramePending(false)
{
    std::srand(std::time(nullptr));
    inputAdapter = std::make_shared<FTXUIInputAdapter>();
    SetupComponents();
    
    // Start animation thread
    animationThread = std::thread(&GameApplication::AnimationLoop, this);
}

GameApplication::~GameApplication() {
    isRunning = false;
    if (animationThread.joinable()) {
        animationThread.join();
    }
}

void GameApplication::AnimationLoop() {
    while (isRunning) {
        if (currentState == AppState::MENU) {
            // Only post if the previous frame has been processed
            if (!animationFramePending) {
                animationFramePending = true;
                screen.Post(Event::Custom);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 20 FPS for smooth waves
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep more when not in menu
        }
    }
}

void GameApplication::SetupComponents() {
    // Menu
    menu_entries = {
        "Play",
        "Leaderboard",
        "Quit"
    };
    
    MenuOption menu_option;
    menu_option.on_enter = [&] {
        if (menu_selected == 0) { // Play
            currentState = AppState::NAME_INPUT;
            playerName = ""; // Reset name
        }
        if (menu_selected == 1) { // Leaderboard
            scoreManager.LoadScores();
            currentState = AppState::LEADERBOARD;
        }
        if (menu_selected == 2) { // Quit
            screen.ExitLoopClosure()();
        }
    };
    menu = Menu(&menu_entries, &menu_selected, menu_option);
    
    // Name Input
    InputOption input_option;
    input_option.on_enter = [&] {
        if (!playerName.empty()) {
            // Trim newline if present
            if (playerName.back() == '\n') {
                playerName.pop_back();
            }
            
            // Initialize game immediately
            auto boardMap = std::make_unique<BoardMap>(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT);
            auto obstacleMgr = std::make_unique<ObstacleManager>(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT);
            auto treasureMgr = std::make_unique<TreasureManager>(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT);
            auto shipMgr = std::make_unique<ShipManager>(GameConstants::MAP_WIDTH/2, GameConstants::MAP_HEIGHT/2, playerName);

            game = std::make_unique<GameEngine>(inputAdapter, 
                                                std::move(obstacleMgr), 
                                                std::move(treasureMgr), 
                                                std::move(shipMgr), 
                                                std::move(boardMap));
            game->Init(playerName); // Init might be redundant now but keeping for safety
            inputAdapter->Reset();
            currentState = AppState::GAME;
        }
    };
    name_input = Input(&playerName, "Enter Ship Name", input_option);
}

Element GameApplication::RenderMenu() {
    // 1. Render Ship
    Elements shipElements;
    for (const auto& line : SHIP_ART) {
        shipElements.push_back(text(line) | center | color(Color::BlueLight));
    }
    
    // 2. Render Waves using Canvas
    auto waveCanvas = Canvas(100, 10); // Width 100, Height 10
    
    static float time = 0.0f;
    time += 0.1f; // Increment time for animation
    
    for (int x = 0; x < 100; ++x) {
        // y = height/2 + amplitude * sin(frequency * x + speed * time)
        float y = 5.0f + 3.0f * std::sin(0.1f * x + time);
        waveCanvas.DrawPoint(x, static_cast<int>(y), true);
        
        // Fill below wave
        for (int fillY = static_cast<int>(y) + 1; fillY < 10; ++fillY) {
             waveCanvas.DrawPoint(x, fillY, true);
        }
    }
    
    return vbox({
        text("PIRATE SHIP GAME") | bold | center | color(Color::Yellow),
        separator(),
        vbox(shipElements),
        canvas(waveCanvas) | center | color(Color::Cyan),
        separator(),
        menu->Render() | center
    }) | borderRounded | color(Color::Green);
}

Element GameApplication::RenderLeaderboard() {
    Elements list;
    list.push_back(text("🏆 LEADERBOARD 🏆") | bold | center | color(Color::Yellow));
    list.push_back(separator());
    
    // Header
    list.push_back(hbox({
        text("Rank") | size(WIDTH, EQUAL, 6) | bold,
        text("Name") | size(WIDTH, EQUAL, 20) | bold,
        text("Score") | size(WIDTH, EQUAL, 10) | bold
    }));
    list.push_back(separator());
    
    auto scores = scoreManager.GetLeaderboard();
    for (size_t i = 0; i < scores.size(); ++i) {
        const auto& entry = scores[i];
        
        std::string rankStr = std::to_string(i + 1);
        Color rowColor = Color::White;
        
        if (i == 0) { rankStr = "🥇"; rowColor = Color::Gold1; }
        else if (i == 1) { rankStr = "🥈"; rowColor = Color::GrayLight; } // Silver approximation
        else if (i == 2) { rankStr = "🥉"; rowColor = Color::Orange1; }   // Bronze approximation
        
        list.push_back(hbox({
            text(rankStr) | size(WIDTH, EQUAL, 6) | center,
            text(entry.name) | size(WIDTH, EQUAL, 20) | color(rowColor),
            text(std::to_string(entry.score)) | size(WIDTH, EQUAL, 10) | color(rowColor)
        }));
    }
    
    if (scores.empty()) {
        list.push_back(text("No scores yet!") | center | color(Color::GrayDark));
    }
    
    list.push_back(separator());
    list.push_back(text("Press 'm' to return to menu") | center);
    
    return vbox(list) | borderRounded | color(Color::Green);
}

Element GameApplication::RenderMain() {
    if (currentState == AppState::MENU) {
        return RenderMenu();
    }
    
    if (currentState == AppState::NAME_INPUT) {
            return vbox({
            text("Who commands this ship?") | center,
            name_input->Render() | center
        }) | borderRounded | color(Color::Green);
    }
    
    if (currentState == AppState::LEADERBOARD) {
        return RenderLeaderboard();
    }
    
    if (currentState == AppState::GAME) {
        if (game) {
            // Game Loop Logic (Rendering part)
            if (obstacle_spawn_counter++ >= GameConstants::OBSTACLE_SPAWN_INTERVAL) {
                obstacle_spawn_counter = 0;
                game->SpawnEntities(); 
            }
            return game->Render();
        } else {
            return text("Loading...") | center;
        }
    }
    
    return text("Error: Unknown State");
}

bool GameApplication::OnEvent(Event event) {
    // Handle animation events
    if (event == Event::Custom) {
        animationFramePending = false; // Acknowledge frame
        return true; // Force redraw
    }

    if (currentState == AppState::MENU) {
        return menu->OnEvent(event);
    }
    
    if (currentState == AppState::NAME_INPUT) {
        return name_input->OnEvent(event);
    }
    
    if (currentState == AppState::LEADERBOARD) {
        if (event == Event::Character('m')) {
            currentState = AppState::MENU;
            return true;
        }
    }
    
    if (currentState == AppState::GAME) {
        if (!game) return false;
        
        inputAdapter->SetLastEvent(event);
        game->Update(); // Was RunLoopStep, now Update, but called synchronously
        
        if (game->IsGameOver() || inputAdapter->isQuitPressed()) {
            // Save Score
            if (game->IsGameOver()) {
                std::cout << "Game Over! Saving score: " << game->GetScore() << " for " << playerName << std::endl;
                scoreManager.SaveScore(playerName, game->GetScore());
            }
            
            game.reset(); // Destroy game instance
            scoreManager.LoadScores(); // Refresh
            currentState = AppState::LEADERBOARD; // Go to leaderboard after game
            return true;
        }
        return true; // Consume event in game
    }
    
    return false;
}

void GameApplication::Run() {
    auto renderer = Renderer([&] { return RenderMain(); });
    auto component = CatchEvent(renderer, [&](Event event) { return OnEvent(event); });
    screen.Loop(component);
}
