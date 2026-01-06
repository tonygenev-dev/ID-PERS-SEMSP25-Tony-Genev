#pragma once
#include <ftxui/dom/elements.hpp>
#include "../engine/GameConstants.hpp"

struct Treasure {
    int x, y;
    int value;
    Treasure(int x, int y, int value = GameConstants::TREASURE_VALUE);
    ftxui::Element Render() const;
};
