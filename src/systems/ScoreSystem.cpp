#include <iostream>
#include <SFML/Graphics.hpp>
#include "ScoreSystem.h"

using namespace std;
using namespace sf;

void ScoreSystem::addJudgement(Judgement judgement)
{
    cout << JudgementSystem::judgementToString(judgement) << endl;
}