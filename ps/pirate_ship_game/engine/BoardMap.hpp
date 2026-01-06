#pragma once
#include <ftxui/dom/elements.hpp>
#include <vector>
#include "Ship.hpp"
#include "ObstacleManager.hpp"
#include "TreasureManager.hpp"

class BoardMap {
    int width, height;

public:
    BoardMap(int width, int height);
    
    ftxui::Element Render(const Ship* ship, const ObstacleManager& obstacleManager, const TreasureManager& treasureManager);
};
