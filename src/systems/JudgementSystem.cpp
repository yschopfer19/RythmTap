#include <iostream>
#include <SFML/Graphics.hpp>

#include "JudgementSystem.h"

using namespace std;
using namespace sf;

Judgement JudgementSystem::evaluate(float hitzoneY, int lane_index, vector<unique_ptr<Note>> &notes)
{
    for (unique_ptr<Note> &note : notes)
    {
        if (note->getlaneIndex() == lane_index)
        {
            HoldNote *holdNote = dynamic_cast<HoldNote *>(note.get());
            if (holdNote != nullptr && holdNote->getState() == NoteState::ACTIVE)
            {
                float distance = abs((holdNote->getPosition().y + holdNote->getNoteLength()) - hitzoneY);
                if (distance < 30)
                {
                    holdNote->startHold(hitzoneY);
                    return Judgement::HOLD;
                }
            }
            else if (note->getState() == NoteState::ACTIVE)
            {
                float distance = abs(note->getPosition().y - hitzoneY);
                if (distance < 10)
                {
                    note->setState(NoteState::HIT);
                    return Judgement::PERFECT;
                    ;
                }
                else if (distance < 30)
                {
                    note->setState(NoteState::HIT);
                    return Judgement::GOOD;
                }
            }
        }
    }
    return Judgement::MISS;
}

Judgement JudgementSystem::evaluateRelease(float hitzoneY, int lane_index, vector<unique_ptr<Note>> &notes)
{
    for (unique_ptr<Note> &note : notes)
    {
        if (note->getlaneIndex() == lane_index)
        {
            HoldNote *holdNote = dynamic_cast<HoldNote *>(note.get());
            if (holdNote != nullptr && holdNote->getState() == NoteState::HELD)
            {
                float distance = abs(holdNote->getPosition().y - hitzoneY);
                if (distance < 30)
                {
                    holdNote->setState(NoteState::HIT);
                    return Judgement::PERFECT;
                }
                else
                {
                    holdNote->setState(NoteState::MISS);
                    return Judgement::MISS;
                }
            }
        }
    }
    return Judgement::RELEASE;
}

string JudgementSystem::judgementToString(Judgement judgement)
{
    switch (judgement)
    {
        case Judgement::PERFECT: return "Perfect!";
        case Judgement::GOOD:    return "Good!";
        case Judgement::MISS:    return "Miss!";
        case Judgement::HOLD:    return "Hold!";
        default:                 return "";
    }
}
