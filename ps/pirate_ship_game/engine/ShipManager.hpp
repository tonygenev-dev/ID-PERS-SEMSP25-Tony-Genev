#pragma once
#include <memory>
#include "Ship.hpp"

class ShipManager {
    std::unique_ptr<Ship> playerShip;

public:
    ShipManager(int startX, int startY, const std::string& name);
    virtual ~ShipManager() = default; // Virtual destructor
    
    virtual Ship* GetShip();
    // Could manage multiple ships later
};
