#include "BoardMap.hpp"
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

BoardMap::BoardMap(int width, int height) : width(width), height(height) {}

Element BoardMap::Render(const Ship* ship, const ObstacleManager& obstacleManager, const TreasureManager& treasureManager) {
    Elements rows;
    for (int y = 0; y < height; ++y) {
        Elements cols;
        for (int x = 0; x < width; ++x) {
            // Check ship
            if (ship->GetX() == x && ship->GetY() == y) {
                cols.push_back(ship->Render() | size(WIDTH, EQUAL, 2));
                continue;
            }
            
            // Check obstacles
            Obstacle* obs = obstacleManager.GetObstacleAt(x, y);
            if (obs) {
                cols.push_back(obs->Render() | size(WIDTH, EQUAL, 2));
                continue;
            }
            
            // Check treasures
            bool isTreasure = false;
            for (const auto& t : treasureManager.GetTreasures()) {
                if (t.x == x && t.y == y) {
                    cols.push_back(t.Render() | size(WIDTH, EQUAL, 2));
                    isTreasure = true;
                    break;
                }
            }
            if (isTreasure) continue;
            
            // Empty
            cols.push_back(text(" ") | size(WIDTH, EQUAL, 2));
        }
        rows.push_back(hbox(cols));
    }
    return vbox(rows) | border;
}
