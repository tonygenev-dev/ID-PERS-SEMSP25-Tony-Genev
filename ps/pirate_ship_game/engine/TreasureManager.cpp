#include "TreasureManager.hpp"
#include <cstdlib>
#include <algorithm>

TreasureManager::TreasureManager(int width, int height) : width(width), height(height) {}

void TreasureManager::SpawnTreasure(int shipX, int shipY) {
    int x = std::rand() % width;
    int y = std::rand() % height;
    
    if (x == shipX && y == shipY) return;
    
    // Check if treasure already exists
    for (const auto& t : treasures) {
        if (t.x == x && t.y == y) return;
    }

    treasures.emplace_back(x, y);
}

int TreasureManager::CollectTreasureAt(int x, int y) {
    int value = 0;
    auto it = std::remove_if(treasures.begin(), treasures.end(), [&](const Treasure& t) {
        if (t.x == x && t.y == y) {
            value = t.value;
            return true;
        }
        return false;
    });
    
    if (it != treasures.end()) {
        treasures.erase(it, treasures.end());
    }
    
    return value;
}

const std::vector<Treasure>& TreasureManager::GetTreasures() const {
    return treasures;
}
