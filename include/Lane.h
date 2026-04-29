#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Lane 
{
public:
    Lane(float x, float y, float width, float height, Color color_lane, Color color_hitzone);
    
    void draw(RenderWindow& window) const;

    Vector2f getHitzonePosition() const;

private:
    RectangleShape shape_lane;
    RectangleShape shape_hitzone;
    Vector2f position_hitzone;
    Vector2f position_lane;
};