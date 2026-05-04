#pragma once
#include "Note.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class HoldNote : public Note
{
public:
    HoldNote(float x, float y, Color color, int speed, int lane_Index, float spawn_time, float note_length);
    void startHold(float hitzoneY);
    void update(float deltatime) override;
    float getNoteLength() const;

private:
    float note_length;
    float hold_end_y;
};