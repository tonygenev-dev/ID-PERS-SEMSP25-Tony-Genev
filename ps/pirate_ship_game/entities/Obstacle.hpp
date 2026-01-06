#pragma once
#include <ftxui/dom/elements.hpp>

// Abstract interface for obstacles
class Obstacle {
public:
    virtual ~Obstacle() = default;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
    virtual ftxui::Element Render() const = 0;
    virtual int OnCollision() const = 0;
};

class Rock : public Obstacle {
    int x, y;
public:
    Rock(int x, int y);
    int GetX() const override;
    int GetY() const override;
    ftxui::Element Render() const override;
    int OnCollision() const override;
};

class EnemyShip : public Obstacle {
    int x, y;
    int direction; // -1 for left, +1 for right
public:
    EnemyShip(int x, int y);
    int GetX() const override;
    int GetY() const override;
    ftxui::Element Render() const override;
    int OnCollision() const override;
    void Update(int min_x, int max_x);
};

class Whirlpool : public Obstacle {
    int x, y;
public:
    Whirlpool(int x, int y);
    int GetX() const override;
    int GetY() const override;
    ftxui::Element Render() const override;
    int OnCollision() const override;
};

class InvisibleRock : public Obstacle {
    int x, y;
    bool isVisible;
public:
    InvisibleRock(int x, int y);
    int GetX() const override;
    int GetY() const override;
    ftxui::Element Render() const override;
    int OnCollision() const override;
};
