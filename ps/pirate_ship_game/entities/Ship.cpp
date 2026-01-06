#include "Ship.hpp"
#include <ftxui/dom/elements.hpp>
#include <algorithm>

Ship::Ship(int startX, int startY, int startHealth, std::string name)
    : x(startX), y(startY), health(startHealth), score(0), name(name) {}

void Ship::Move(int dx, int dy, int maxX, int maxY) {
    x = std::max(0, std::min(maxX, x + dx));
    y = std::max(0, std::min(maxY, y + dy));
}

void Ship::TakeDamage(int amount) {
    health += amount; // amount is usually negative for damage in this game logic
}

void Ship::AddScore(int amount) {
    score += amount;
}

ftxui::Element Ship::Render() const {
    using namespace ftxui;
    return text("⛵") | center | bold | color(Color::Blue);
}

int Ship::GetX() const { return x; }
int Ship::GetY() const { return y; }
int Ship::GetHealth() const { return health; }
int Ship::GetScore() const { return score; }
std::string Ship::GetName() const { return name; }
