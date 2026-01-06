#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include "ObstacleManager.hpp"

TEST(ObstacleManagerTest, SpawnsObstacles) {
    ObstacleManager manager(20, 10);
    manager.SpawnObstacle(0, 0);
    
    // We can't guarantee spawn because of random chance or collision with ship, 
    // but we can try multiple times or check if empty initially.
    // Let's just check if we can get the list.
    const auto& obstacles = manager.GetObstacles();
    // Initially empty? No, we just spawned one (maybe).
    
    // Let's force spawn a few
    for(int i=0; i<100; ++i) manager.SpawnObstacle(0, 0);
    
    EXPECT_FALSE(manager.GetObstacles().empty());
}

TEST(ObstacleManagerTest, RemoveObstacle) {
    ObstacleManager manager(20, 10);
    // Mocking random is hard without dependency injection for RNG, 
    // but we can check if Remove works if we find one.
    
    // Let's manually insert if we could, but we can't easily access private vector.
    // We'll rely on public API.
    for(int i=0; i<50; ++i) manager.SpawnObstacle(5, 5); // Avoid 5,5
    
    // Find an obstacle
    int ox = -1, oy = -1;
    for(const auto& obs : manager.GetObstacles()) {
        ox = obs->GetX();
        oy = obs->GetY();
        break;
    }
    
    if(ox != -1) {
        manager.RemoveObstacleAt(ox, oy);
        EXPECT_EQ(manager.GetObstacleAt(ox, oy), nullptr);
    }
}
