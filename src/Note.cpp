#include <iostream>
#include <SFML/Graphics.hpp>

#include "Note.h"

using namespace std;
using namespace sf;

Note::Note(float x, float y, float width, float height, Color color, int speed, int lane_Index, float spawn_time)
    : position(x, y), speed(speed), lane_Index(lane_Index), spawn_time(spawn_time)
{
    shape.setPosition({x, y});
    shape.setSize({width, height});
    shape.setFillColor(color);
}

void Note::draw(RenderWindow &window) const
{
    window.draw(shape);
}

void Note::update(float deltatime)
{
    position.y += speed * deltatime;
    shape.setPosition(position);
}

Vector2f Note::getPosition() const
{
    return position;
}

int Note::getlaneIndex() const
{
    return lane_Index;
}

float Note::getSpawnTime() const
{
    return spawn_time;
}

NoteState Note::getState() const
{
    return this->state;
}

void Note::setState(NoteState state)
{
    this->state = state;
}
