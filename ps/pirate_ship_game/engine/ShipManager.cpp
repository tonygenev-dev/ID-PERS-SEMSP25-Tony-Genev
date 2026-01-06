#include "ShipManager.hpp"

ShipManager::ShipManager(int startX, int startY, const std::string& name) {
    playerShip = std::make_unique<Ship>(startX, startY, 3, name);
}

Ship* ShipManager::GetShip() {
    return playerShip.get();
}
