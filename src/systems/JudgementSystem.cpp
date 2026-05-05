#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "JudgementSystem.h"
#include "Types.h"

using namespace std;
using namespace sf;

Judgement JudgementSystem::evaluatePress(
    LaneIndex lane,
    float hitzoneY,
    const vector<unique_ptr<Note>> &notes,
    Seconds time)
{
    for (const auto &note : notes)
    {
        if (note->getlaneIndex() != lane.value)
            continue;

        if (note->getState() != NoteState::ACTIVE)
            continue;

        float distance = abs(note->getPosition().y - hitzoneY);

        if (distance < 22.0f)
        {
            note->setState(NoteState::HIT);
            return Judgement::PERFECT;
        }
        else if (distance < 35.0f)
        {
            note->setState(NoteState::HIT);
            return Judgement::GOOD;
        }
    }

    return Judgement::MISS;
}

Judgement JudgementSystem::evaluateRelease(
    LaneIndex lane,
    float hitzoneY,
    const vector<unique_ptr<Note>> &notes)
{
    for (const auto &note : notes)
    {
        if (note->getlaneIndex() != lane.value)
            continue;

        if (note->getState() != NoteState::HELD)
            continue;

        float distance = abs(note->getPosition().y - hitzoneY);

        if (distance < 30.0f)
        {
            note->setState(NoteState::HIT);
            return Judgement::PERFECT;
        }

        note->setState(NoteState::MISS);
        return Judgement::MISS;
    }

    return Judgement::RELEASE;
}

string JudgementSystem::judgementToString(Judgement judgement)
{
    switch (judgement)
    {
    case Judgement::PERFECT:
        return "Perfect!";
    case Judgement::GOOD:
        return "Good!";
    case Judgement::MISS:
        return "Miss!";
    case Judgement::HOLD:
        return "Hold!";
    case Judgement::RELEASE:
        return "Release!";
    default:
        return "";
    }
}
