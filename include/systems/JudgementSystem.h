#include <iostream>
#include <SFML/Graphics.hpp>

#include "Note.h"
#include "HoldNote.h"

using namespace std;
using namespace sf;

enum class Judgement
{
    PERFECT,
    GOOD,
    MISS,
    HOLD, 
    RELEASE
};

class JudgementSystem
{
    public:
    static Judgement evaluate(float hitzoneY, int lane_index, vector<unique_ptr<Note>> &notes);
    static Judgement  evaluateRelease(float hitzoneY, int lane_index, vector<unique_ptr<Note>> &notes);
    static string judgementToString(Judgement judgement);

};

