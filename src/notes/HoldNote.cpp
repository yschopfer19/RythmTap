#include <iostream>
#include <SFML/Graphics.hpp>

#include "HoldNote.h"

using namespace std;
using namespace sf;

HoldNote::HoldNote(float x, float y, Color color, int speed, int lane_Index, float spawn_time, float note_length)
    : Note(x, y, color, speed, lane_Index, spawn_time), note_length(note_length), hold_end_y(0.0f)
{
    shape.setSize({100, note_length});
}

void HoldNote::startHold(float hitzoneY)
{
    setState(NoteState::HELD);
    hold_end_y = position.y + note_length;
    shape.setPosition(position);
}

void HoldNote::update(float deltatime)
{
    if (state == NoteState::HELD)
    {
        note_length -= speed * deltatime;
        if (note_length <= 0.0f)
        {
            note_length = 0.0f;
            setState(NoteState::HIT);
        }

        position.y = hold_end_y - note_length;
        shape.setSize({shape.getSize().x, note_length});
        shape.setPosition(position);
    }
    else
    {
        Note::update(deltatime);
    }
}

float HoldNote::getNoteLength() const
{
    return this->note_length;
}