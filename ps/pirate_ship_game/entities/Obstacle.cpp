#include "Obstacle.hpp"

// Rock
Rock::Rock(int x, int y) : x(x), y(y) {}
int Rock::GetX() const { return x; }
int Rock::GetY() const { return y; }
ftxui::Element Rock::Render() const {
    return ftxui::text("🔴") | ftxui::center | ftxui::color(ftxui::Color::Red);
}
int Rock::OnCollision() const { return -1; }

// EnemyShip
EnemyShip::EnemyShip(int x, int y) : x(x), y(y), direction(1) {}
int EnemyShip::GetX() const { return x; }
int EnemyShip::GetY() const { return y; }
ftxui::Element EnemyShip::Render() const {
    return ftxui::text("🛥️") | ftxui::center | ftxui::color(ftxui::Color::Magenta);
}
int EnemyShip::OnCollision() const { return -2; }
void EnemyShip::Update(int min_x, int max_x) {
    x += direction;
    if (x <= min_x) {
        x = min_x;
        direction = 1;
    } else if (x >= max_x) {
        x = max_x;
        direction = -1;
    }
}

// Whirlpool
Whirlpool::Whirlpool(int x, int y) : x(x), y(y) {}
int Whirlpool::GetX() const { return x; }
int Whirlpool::GetY() const { return y; }
ftxui::Element Whirlpool::Render() const {
    return ftxui::text("🌀") | ftxui::center | ftxui::color(ftxui::Color::Cyan);
}
int Whirlpool::OnCollision() const { return -3; }

// InvisibleRock
InvisibleRock::InvisibleRock(int x, int y) : x(x), y(y), isVisible(false) {}
int InvisibleRock::GetX() const { return x; }
int InvisibleRock::GetY() const { return y; }
ftxui::Element InvisibleRock::Render() const {
    if (isVisible) {
        return ftxui::text("🔴") | ftxui::center | ftxui::color(ftxui::Color::Red); // Reveals as rock
    }
    return ftxui::text(" "); // Invisible
}
int InvisibleRock::OnCollision() const { 
    // Maybe it becomes visible on collision?
    // const_cast<InvisibleRock*>(this)->isVisible = true; // Hacky, but for now just return damage
    return -1; 
}
