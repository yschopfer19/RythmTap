#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "../systems/InputSystem.h"
#include "../systems/NoteSystem.h"
#include "../systems/JudgementSystem.h"
#include "../systems/ScoreSystem.h"
#include "../audio/AudioSystem.h"
#include "../charts/Chart.h"
#include "Lane.h"
#include "Types.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void loadChart(const Chart &chart);

private:
    sf::RenderWindow window;

    float elapsedTime = 0.0f; // Verstrichene Zeit seit Start

    std::array<Lane, 4> lanes;

    InputSystem inputSystem;
    NoteSystem noteSystem;
    JudgementSystem judgementSystem;
    ScoreSystem scoreSystem;
    AudioSystem audioSystem;
};