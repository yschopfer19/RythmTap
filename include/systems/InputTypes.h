#pragma once

#include "Types.h"

enum class InputAction
{
    Press,
    Release
};

struct InputEvent
{
    LaneIndex lane;
    InputAction action;
};