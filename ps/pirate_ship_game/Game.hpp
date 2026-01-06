#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Obstacle.hpp"
#include "Treasure.hpp"

class Game {
public:
    int ship_x = 0;
    int ship_y = 0;
    const int width = 20;
    const int height = 10;
    int lives = 3;
    int score = 0;

    std::vector<std::unique_ptr<Obstacle>> obstacles;  // Using smart pointers for obstacle objects
    std::vector<Treasure> treasures;

    // Move ship, but do not move into an obstacle tile
    void MoveShip(int dx, int dy) {
        int new_x = std::max(0, std::min(width - 1, ship_x + dx));
        int new_y = std::max(0, std::min(height - 1, ship_y + dy));

        // Check for obstacle at new position
        for (auto& o : obstacles) {
            if (o->GetX() == new_x && o->GetY() == new_y) {
                // Collision happened: reduce lives and remove obstacle
                lives += o->OnCollision();
                obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                    [&](const std::unique_ptr<Obstacle>& obs) {
                        return obs->GetX() == new_x && obs->GetY() == new_y;
                    }), obstacles.end());
                return; // Do not move ship into obstacle position
            }
        }
        // No obstacle - move freely
        ship_x = new_x;
        ship_y = new_y;
    }

    void SpawnObstacle() {
        int type = std::rand() % 3;
        int x = std::rand() % width;
        int y = std::rand() % height;
        if (x == ship_x && y == ship_y) return;
        switch (type) {
        case 0: obstacles.emplace_back(std::make_unique<Rock>(x, y)); break;
        case 1: obstacles.emplace_back(std::make_unique<EnemyShip>(x, y)); break;
        case 2: obstacles.emplace_back(std::make_unique<Whirlpool>(x, y)); break;
        }
    }

    void SpawnTreasure() {
        int x = std::rand() % width;
        int y = std::rand() % height;
        if (x == ship_x && y == ship_y) return;
        treasures.emplace_back(x, y);
    }

    void CollectTreasures() {
        treasures.erase(std::remove_if(treasures.begin(), treasures.end(), [&](const Treasure& t) {
            if (t.x == ship_x && t.y == ship_y) {
                score += 10;
                return true;
            }
            return false;
            }), treasures.end());
    }
void UpdateEnemyShips() {
    for (auto& obs : obstacles) {
        EnemyShip* es = dynamic_cast<EnemyShip*>(obs.get());
        if (es) {
            es->Update(0, width - 1); // Pass limits of your board
        }
    }
}

    bool HandleCollisions() {
        // Remaining collision logic can be here, but handled in MoveShip
        return lives <= 0;
    }
};
