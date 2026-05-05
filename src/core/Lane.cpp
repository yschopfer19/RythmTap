#include <SFML/Graphics.hpp>

#include "Lane.h"

using namespace sf;

Lane::Lane(float x, float y, float width, float height, Color color_lane, Color color_hitzone)
    : position_hitzone(x, y + height - 20), position_lane(x, y)
{
    shape_lane.setPosition({position_lane});
    shape_lane.setSize({width, height});
    shape_lane.setFillColor(color_lane);
    shape_hitzone.setPosition({position_hitzone});
    shape_hitzone.setSize({width, 20});
    shape_hitzone.setFillColor(color_hitzone);
}

void Lane::draw(RenderWindow &window) const
{
    window.draw(shape_lane);
    window.draw(shape_hitzone);
}

Vector2f Lane::getHitzonePosition() const { return position_hitzone; }