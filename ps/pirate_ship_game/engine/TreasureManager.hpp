#pragma once
#include <vector>
#include "Treasure.hpp"

class TreasureManager {
    std::vector<Treasure> treasures;
    int width, height;

public:
    TreasureManager(int width, int height);
    virtual ~TreasureManager() = default; // Virtual destructor
    
    virtual void SpawnTreasure(int shipX, int shipY);
    // Returns value of treasure collected, or 0 if none
    virtual int CollectTreasureAt(int x, int y);
    
    virtual const std::vector<Treasure>& GetTreasures() const;
};
