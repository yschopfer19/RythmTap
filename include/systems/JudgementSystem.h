#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Types.h"
#include "InputTypes.h"
#include "Note.h"

enum class Judgement
{
    PERFECT,
    GOOD,
    MISS,
    HOLD,
    RELEASE,
    NONE
};

class JudgementSystem
{
public:
    Judgement evaluatePress(
        LaneIndex lane,
        float hitzoneY,
        const std::vector<std::unique_ptr<Note>> &notes,
        Seconds time);

    Judgement evaluateRelease(
        LaneIndex lane,
        float hitzoneY,
        const std::vector<std::unique_ptr<Note>> &notes);

    static std::string judgementToString(Judgement judgement);
};