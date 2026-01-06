#pragma once
#include <memory>
#include "IInputHandler.hpp"
#include "ObstacleManager.hpp"
#include "TreasureManager.hpp"
#include "ShipManager.hpp"
#include "BoardMap.hpp"

class GameEngine {
    std::shared_ptr<IInputHandler> inputHandler;
    std::unique_ptr<ObstacleManager> obstacleManager;
    std::unique_ptr<TreasureManager> treasureManager;
    std::unique_ptr<ShipManager> shipManager;
    std::unique_ptr<BoardMap> boardMap;
    
    int width, height;
    bool gameOver;

public:
    GameEngine(std::shared_ptr<IInputHandler> inputHandler,
               std::unique_ptr<ObstacleManager> obstacleManager,
               std::unique_ptr<TreasureManager> treasureManager,
               std::unique_ptr<ShipManager> shipManager,
               std::unique_ptr<BoardMap> boardMap);
    
    void Init(const std::string& playerName);
    void Update(); // Single step of game loop
    
    // Getters for testing/rendering
    bool IsGameOver() const;
    int GetScore() const;
    ftxui::Element Render();
    
    // Actions
    void MoveShip(GameDirection dir);
    void SpawnEntities();
    void CheckCollisions();
};
