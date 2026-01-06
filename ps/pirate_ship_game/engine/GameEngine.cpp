#include "GameEngine.hpp"
#include "GameConstants.hpp"
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

GameEngine::GameEngine(std::shared_ptr<IInputHandler> inputHandler,
                       std::unique_ptr<ObstacleManager> obstacleManager,
                       std::unique_ptr<TreasureManager> treasureManager,
                       std::unique_ptr<ShipManager> shipManager,
                       std::unique_ptr<BoardMap> boardMap)
    : inputHandler(inputHandler),
      obstacleManager(std::move(obstacleManager)),
      treasureManager(std::move(treasureManager)),
      shipManager(std::move(shipManager)),
      boardMap(std::move(boardMap)),
      width(GameConstants::MAP_WIDTH),
      height(GameConstants::MAP_HEIGHT),
      gameOver(false)
{
}

void GameEngine::Init(const std::string& playerName) {
    // Managers are injected, so we don't create them here.
}

void GameEngine::MoveShip(GameDirection dir) {
    if (gameOver) return;
    
    int dx = 0, dy = 0;
    switch (dir) {
        case GameDirection::Up: dy = -1; break;
        case GameDirection::Down: dy = 1; break;
        case GameDirection::Left: dx = -1; break;
        case GameDirection::Right: dx = 1; break;
        default: return;
    }
    
    Ship* ship = shipManager->GetShip();
    int newX = std::max(0, std::min(width - 1, ship->GetX() + dx));
    int newY = std::max(0, std::min(height - 1, ship->GetY() + dy));
    
    // Check obstacle collision BEFORE moving? Or move then check?
    // Original logic: "Check for obstacle at new position"
    Obstacle* obs = obstacleManager->GetObstacleAt(newX, newY);
    if (obs) {
        ship->TakeDamage(obs->OnCollision());
        obstacleManager->RemoveObstacleAt(newX, newY);
        // Don't move
    } else {
        ship->Move(dx, dy, width - 1, height - 1);
    }
}

void GameEngine::SpawnEntities() {
    // Logic to spawn periodically could be here or driven by main loop
    // For now, let's expose methods or call them here if we had a frame counter
    // We'll rely on caller to call SpawnEntities periodically or handle counters
    obstacleManager->SpawnObstacle(shipManager->GetShip()->GetX(), shipManager->GetShip()->GetY());
    treasureManager->SpawnTreasure(shipManager->GetShip()->GetX(), shipManager->GetShip()->GetY());
}

void GameEngine::CheckCollisions() {
    Ship* ship = shipManager->GetShip();
    if (ship->GetHealth() <= 0) {
        gameOver = true;
    }
    
    // Check treasure
    int value = treasureManager->CollectTreasureAt(ship->GetX(), ship->GetY());
    if (value > 0) {
        ship->AddScore(value);
    }
    
    // Update enemies
    obstacleManager->UpdateObstacles();
    
    // Check collision with dynamic enemies (if they moved into ship)
    Obstacle* obs = obstacleManager->GetObstacleAt(ship->GetX(), ship->GetY());
    if (obs) {
        ship->TakeDamage(obs->OnCollision());
        obstacleManager->RemoveObstacleAt(ship->GetX(), ship->GetY());
    }
}

void GameEngine::Update() {
    if (gameOver) return;
    
    // 1. Handle Input
    GameDirection dir = inputHandler->readInput();
    if (dir != GameDirection::None) {
        MoveShip(dir);
    }
    
    // 2. Check Collisions & Update State
    CheckCollisions();
}

bool GameEngine::IsGameOver() const {
    return gameOver;
}

int GameEngine::GetScore() const {
    return shipManager->GetShip()->GetScore();
}

Element GameEngine::Render() {
    if (gameOver) {
        return vbox({
            text("GAME OVER") | bold | color(Color::Red) | center,
            text("Final Score: " + std::to_string(shipManager->GetShip()->GetScore())) | center
        }) | border;
    }
    
    return vbox({
        hbox({
            text("Lives: ") | bold | color(Color::Red),
            text(std::to_string(shipManager->GetShip()->GetHealth())),
            text("   Score: ") | bold | color(Color::Green),
            text(std::to_string(shipManager->GetShip()->GetScore()))
        }) | center,
        boardMap->Render(shipManager->GetShip(), *obstacleManager, *treasureManager) | center
    });
}
