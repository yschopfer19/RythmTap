#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "JudgementSystem.h"
#include "Types.h"
#include "HoldNote.h"

using namespace std;
using namespace sf;

Judgement JudgementSystem::evaluatePress(
    LaneIndex lane,
    float hitzoneY,
    const vector<unique_ptr<Note>> &notes,
    float songtime)  // ← Seconds → float
{
    for (const auto &note : notes)
    {
        if (note->getlaneIndex() != lane.value)
            continue;

        if (note->getState() != NoteState::ACTIVE)
            continue;

        // Prüfe ob HoldNote
        HoldNote* holdNote = dynamic_cast<HoldNote*>(note.get());
        if (holdNote != nullptr)
        {
            Judgement result = Judgement::MISS;
            holdNote->onPress(hitzoneY, result);
            return result;
        }

        // Normale Note
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

Judgement JudgementSystem::evaluateRelease(LaneIndex lane, float hitzoneY, vector<unique_ptr<Note>>& notes)
{
    for (const auto &note : notes)
    {
        if (note->getlaneIndex() != lane.value) continue;
        if (note->getState() != NoteState::HELD) continue;

        HoldNote* holdNote = dynamic_cast<HoldNote*>(note.get());
        if (holdNote != nullptr)
        {
            Judgement result = Judgement::RELEASE;
            holdNote->onRelease(hitzoneY, result);
            return result;
        }
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
