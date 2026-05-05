#include "Game.h"
#include "../charts/ChartLoader.h"
#include <array>
#include "GameConfig.h"

using namespace std;
using namespace sf;

Game::Game()
    : window(sf::VideoMode({800, 600}), "Rhythm Game"),
      lanes({Lane(50.0f, 50.0f, 130.0f, 500.0f, Color::Blue, Color::White),
             Lane(220.0f, 50.0f, 130.0f, 500.0f, Color::Blue, Color::White),
             Lane(390.0f, 50.0f, 130.0f, 500.0f, Color::Blue, Color::White),
             Lane(560.0f, 50.0f, 130.0f, 500.0f, Color::Blue, Color::White)})
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    if (!audioSystem.load("C:/Users/yanni/Desktop/RhythmTap/assets/music/fassounds-escape-your-love-upbeat-fashion-pop-dance-412230.ogg"))
    {
        cout << "Fehler beim Laden der Musik!" << endl;
    }

    Chart testChart = ChartLoader::createTestChart();
    loadChart(testChart);

    audioSystem.play();
}

void Game::loadChart(const Chart &chart)
{
    const auto &notes = chart.getNotes();

    for (const auto &chartNote : notes)
    {
        float hitTime = chartNote.time;
        float spawnTime = max(0.0f, hitTime - GameConfig::NOTE_TRAVEL_TIME);

        auto note = make_unique<Note>(
            lanes[chartNote.lane].getHitzonePosition().x,
            -50.0f,
            Color::White,
            GameConfig::NOTE_SPEED,
            chartNote.lane,
            spawnTime);

        noteSystem.addNote(move(note));
    }
}

void Game::run()
{
    Clock clock;

    while (window.isOpen())
    {
        // Time elapsed = clock.restart();
        // Seconds dt{ elapsed.asSeconds() };

        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    auto event = window.pollEvent();
    while (event)
    {
        if (event->is<Event::Closed>())
            window.close();

        inputSystem.handleEvent(*event);
        event = window.pollEvent();
    }
}

void Game::update()
{
    Seconds time = audioSystem.getSongTime();

    array<float, 4> hitY;
    for (int i = 0; i < 4; i++)
        hitY[i] = lanes[i].getHitzonePosition().y;

    noteSystem.update(time, hitY);

    auto inputs = inputSystem.pollInputs();

    for (const auto &input : inputs)
    {
        Judgement judgement;
        if (input.action == InputAction::Press)
        {
            judgement = judgementSystem.evaluatePress(
                input.lane,
                hitY[input.lane.value],
                noteSystem.getNotes(),
                time);
        }
        else
        {
            judgement = judgementSystem.evaluateRelease(
                input.lane,
                hitY[input.lane.value],
                noteSystem.getNotes());
        }

        scoreSystem.addJudgement(judgement);
    }
}

void Game::render()
{
    window.clear(Color::Black);

    for (const auto &lane : lanes)
    {
        lane.draw(window);
    }

    noteSystem.draw(window);

    window.display();
}
