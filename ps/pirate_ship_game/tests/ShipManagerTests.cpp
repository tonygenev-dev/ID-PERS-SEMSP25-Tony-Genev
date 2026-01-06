#include <gtest/gtest.h>
#include "ShipManager.hpp"
#include "GameConstants.hpp"

TEST(ShipManagerTest, Initialization) {
    ShipManager manager(10, 10, "TestShip");
    auto ship = manager.GetShip();
    
    ASSERT_NE(ship, nullptr);
    EXPECT_EQ(ship->GetX(), 10);
    EXPECT_EQ(ship->GetY(), 10);
}

TEST(ShipManagerTest, ShipMovement) {
    ShipManager manager(10, 10, "TestShip");
    auto ship = manager.GetShip();
    
    // Simulate movement logic (usually handled by GameEngine calling Ship methods, 
    // but ShipManager owns the ship)
    // ShipManager currently just holds the ship, so we test if we can access and modify it.
    
    // If ShipManager had Move() method, we'd test it here.
    // Since it exposes the Ship*, we verify we got the right one.
    EXPECT_EQ(ship->GetX(), 10);
}
