#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum class NoteState
{
    WAITING,
    ACTIVE,
    HIT,
    MISS,
    HELD,
    RELEASED,
    BROKEN
};

class Note
{
public:
    Note(float x, float y, sf::Color color, int speed, int lane_Index, float spawn_time);

    virtual ~Note() = default;

    virtual void draw(RenderWindow &window) const;

    virtual void update(float deltatime);

    Vector2f getPosition() const;
    int getlaneIndex() const;

    float getSpawnTime() const;

    NoteState getState() const;
    void setState(NoteState state);

protected:
    RectangleShape shape;
    Vector2f position;
    int speed;
    int lane_Index;
    float spawn_time;
    NoteState state = NoteState::WAITING;
};
