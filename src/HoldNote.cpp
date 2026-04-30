#include <iostream>
#include <SFML/Graphics.hpp>

#include "HoldNote.h"

using namespace std;
using namespace sf;

HoldNote::HoldNote(float x, float y, float width, float height, Color color, int speed, int lane_Index, float spawn_time, float note_length)
    : Note(x, y, width, height, color, speed, lane_Index, spawn_time), note_length(note_length), isBeingHeld(false)
{
    shape.setSize({width, note_length});
}

void HoldNote::update(float deltatime)
{
    Note::update(deltatime);

    if (this->state == NoteState::HELD)
    {
    }
}

float HoldNote::getNoteLength() const
{
    return this->note_length;
}