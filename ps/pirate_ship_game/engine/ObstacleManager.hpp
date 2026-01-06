#pragma once
#include <vector>
#include <memory>
#include "Obstacle.hpp"

class ObstacleManager {
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    int width, height;

public:
    ObstacleManager(int width, int height);
    virtual ~ObstacleManager() = default; // Virtual destructor
    
    virtual void SpawnObstacle(int shipX, int shipY);
    virtual void UpdateObstacles();
    virtual void RemoveObstacleAt(int x, int y);
    
    // Returns pointer to obstacle at (x,y) or nullptr
    virtual Obstacle* GetObstacleAt(int x, int y) const;
    
    virtual const std::vector<std::unique_ptr<Obstacle>>& GetObstacles() const;
};
