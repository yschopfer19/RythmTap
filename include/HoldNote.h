#pragma once
#include "Note.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class HoldNote : public Note
{
public:
    HoldNote(float x, float y, float width, float height, Color color, int speed, int lane_Index, float spawn_time, float note_length);
    void update(float deltatime) override;
    float getNoteLength() const;

private:
    bool isBeingHeld;
    float note_length;
};