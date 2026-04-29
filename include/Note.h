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
    MISS
};

class Note
{
public:
    Note(float x, float y, float width, float height, sf::Color color, int speed, int lane_Index, float spawn_time);

    void draw(RenderWindow &window) const;

    void update(float deltatime);

    Vector2f getPosition() const;
    int getlaneIndex() const;

    float getSpawnTime() const;

    NoteState getState() const;
    void setState(NoteState state);

private:
    RectangleShape shape;
    Vector2f position;
    int speed;
    int lane_Index;
    bool got_Hit = false;
    float spawn_time;
    bool spawned = false;
    NoteState state = NoteState::WAITING;
};
