#pragma once
#include <string>
#include <ftxui/dom/elements.hpp>
#include "../engine/GameConstants.hpp"

class Ship {
    int x, y;
    int health;
    int score;
    std::string name;

public:
    Ship(int startX, int startY, int startHealth = GameConstants::INITIAL_LIVES, std::string name = "Player");
    
    void Move(int dx, int dy, int maxX, int maxY);
    void TakeDamage(int amount);
    void AddScore(int amount);
    
    int GetX() const;
    int GetY() const;
    int GetHealth() const;
    int GetScore() const;
    std::string GetName() const;

    ftxui::Element Render() const;
};
