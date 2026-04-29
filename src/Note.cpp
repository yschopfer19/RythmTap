#include <iostream>
#include <SFML/Graphics.hpp>

#include "Note.h"

using namespace std;
using namespace sf;

Note::Note(float x, float y, float width, float height, Color color, int speed, int lane_Index)
    : position(x, y), speed(speed), lane_Index(lane_Index)
{
    shape.setPosition({x, y});
    shape.setSize({width, height});
    shape.setFillColor(color);
}

void Note::draw(RenderWindow& window) const
 {
    window.draw(shape);
}

void Note::update(float deltatime) {
    position.y += speed * deltatime; 
    shape.setPosition(position); 
}

Vector2f Note::getPosition() const {
    return position;
}

int Note::getlaneIndex() const {
    return lane_Index;
}