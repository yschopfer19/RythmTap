#pragma once
#include "Note.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "JudgementSystem.h"

using namespace std;
using namespace sf;

class HoldNote : public Note
{
public:
    HoldNote(float x, float y, Color color, int speed, int lane_Index, float spawn_time, float note_length);
    void update(float songtime) override;
    float getNoteLength() const;
    void onPress(float hitzoneY, Judgement& outJudgement);
    void onRelease(float hitzoneY, Judgement& outJudgement);

private:
    float note_length;
    float hold_end_y = 0.0f;
    float lastTime = -1.0f;
};