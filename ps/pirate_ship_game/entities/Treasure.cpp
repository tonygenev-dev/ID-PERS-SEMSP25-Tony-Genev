#include "Treasure.hpp"

Treasure::Treasure(int x, int y, int value) : x(x), y(y), value(value) {}

ftxui::Element Treasure::Render() const {
    using namespace ftxui;
    return text("💰") | center | color(Color::Yellow);
}
