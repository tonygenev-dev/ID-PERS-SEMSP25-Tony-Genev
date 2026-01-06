#include "ObstacleManager.hpp"
#include <cstdlib>
#include <algorithm>

ObstacleManager::ObstacleManager(int width, int height) : width(width), height(height) {}

void ObstacleManager::SpawnObstacle(int shipX, int shipY) {
    int type = std::rand() % 3;
    int x = std::rand() % width;
    int y = std::rand() % height;
    
    // Simple check to avoid spawning on ship, though game logic might handle collision immediately
    if (x == shipX && y == shipY) return;

    // Check if obstacle already exists there
    if (GetObstacleAt(x, y)) return;

    switch (type) {
    case 0: obstacles.emplace_back(std::make_unique<Rock>(x, y)); break;
    case 1: obstacles.emplace_back(std::make_unique<EnemyShip>(x, y)); break;
    case 2: obstacles.emplace_back(std::make_unique<Whirlpool>(x, y)); break;
    }
}

void ObstacleManager::UpdateObstacles() {
    for (auto& obs : obstacles) {
        EnemyShip* es = dynamic_cast<EnemyShip*>(obs.get());
        if (es) {
            es->Update(0, width - 1);
        }
    }
}

void ObstacleManager::RemoveObstacleAt(int x, int y) {
    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
        [&](const std::unique_ptr<Obstacle>& obs) {
            return obs->GetX() == x && obs->GetY() == y;
        }), obstacles.end());
}

Obstacle* ObstacleManager::GetObstacleAt(int x, int y) const {
    for (const auto& obs : obstacles) {
        if (obs->GetX() == x && obs->GetY() == y) {
            return obs.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Obstacle>>& ObstacleManager::GetObstacles() const {
    return obstacles;
}
