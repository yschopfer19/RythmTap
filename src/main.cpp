#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Lane.h"
#include "Note.h"
#include "HoldNote.h"
#include "JudgementSystem.h"

using namespace std;
using namespace sf;


int main()
{
    RenderWindow window(VideoMode({800, 600}), "Rhythm Game");

    // options for later
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    Lane lanes[] = {
        Lane(50, 100, 100, 200, Color::White, Color::Yellow),
        Lane(250, 100, 100, 200, Color::White, Color::Yellow),
        Lane(450, 100, 100, 200, Color::White, Color::Yellow),
        Lane(650, 100, 100, 200, Color::White, Color::Yellow)};

    vector<unique_ptr<Note>> notes;
    notes.push_back(make_unique<Note>(50, 100, Color::Red, 50, 0, 1.0f));
    notes.push_back(make_unique<Note>(50, 100, Color::Red, 50, 0, 2.0f));
    notes.push_back(make_unique<Note>(250, 100, Color::Red, 50, 1, 5.0f));
    notes.push_back(make_unique<HoldNote>(50, 100, Color::Red, 50, 0, 6.5f, 80));
    notes.push_back(make_unique<Note>(650, 100, Color::Blue, 50, 3, 8.0f));
    notes.push_back(make_unique<Note>(450, 100, Color::Blue, 50, 2, 8.0f));
    notes.push_back(make_unique<HoldNote>(450, 100, Color::Blue, 50, 2, 10.0f, 70));

    Clock clock;

    float gameTime = 0.0f;

    Music music;
    if (!music.openFromFile("../assets/music/fassounds-escape-your-love-upbeat-fashion-pop-dance-412230.ogg"))
    {
        cout << "Fehler beim Laden der Musik!" << endl;
        return -1;
    }
    music.play();

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (auto *keyEvent = event->getIf<Event::KeyPressed>())
            {
                switch (keyEvent->scancode)
                {
                case Keyboard::Scancode::D:
                    cout << JudgementSystem::judgementToString(JudgementSystem::evaluate(lanes[0].getHitzonePosition().y, 0, notes));
                    break;
                case Keyboard::Scancode::F:
                    cout << JudgementSystem::judgementToString(JudgementSystem::evaluate(lanes[1].getHitzonePosition().y, 1, notes));
                    break;
                case Keyboard::Scancode::J:
                    cout << JudgementSystem::judgementToString(JudgementSystem::evaluate(lanes[2].getHitzonePosition().y, 2, notes));
                    break;
                case Keyboard::Scancode::K:
                    cout << JudgementSystem::judgementToString(JudgementSystem::evaluate(lanes[3].getHitzonePosition().y, 3, notes));
                    break;
                }
            }
            else if (auto *keyEvent = event->getIf<Event::KeyReleased>())
            {
                switch (keyEvent->scancode)
                {
                case Keyboard::Scancode::D:
                    cout << JudgementSystem::judgementToString(JudgementSystem::evaluateRelease(lanes[0].getHitzonePosition().y, 0, notes));
                    break;
                case Keyboard::Scancode::F:
                    cout << JudgementSystem::judgementToString(JudgementSystem::evaluateRelease(lanes[1].getHitzonePosition().y, 1, notes));
                    break;
                case Keyboard::Scancode::J:
                    cout << JudgementSystem::judgementToString(JudgementSystem::evaluateRelease(lanes[2].getHitzonePosition().y, 2, notes));
                    break;
                case Keyboard::Scancode::K:
                    cout << JudgementSystem::judgementToString(JudgementSystem::evaluateRelease(lanes[3].getHitzonePosition().y, 3, notes));
                    break;
                }
            }

            if (event->is<Event::Closed>())
                window.close();
        }

        Time time = clock.restart();
        float deltatime = time.asSeconds();

        gameTime += deltatime;

        window.clear(Color::Black);

        for (const Lane &lane : lanes)
        {
            lane.draw(window);
        }

        for (unique_ptr<Note> &note : notes)
        {
            if (note->getState() == NoteState::WAITING && gameTime >= note->getSpawnTime())
            {
                note->setState(NoteState::ACTIVE);
            }

            if (note->getState() == NoteState::ACTIVE && note->getPosition().y > lanes[note->getlaneIndex()].getHitzonePosition().y + 30)
            {
                note->setState(NoteState::MISS);
            }

            if (note->getState() == NoteState::ACTIVE || note->getState() == NoteState::HELD)
            {
                note->update(deltatime);
                note->draw(window);
            }
        }
        // cout << note.getPosition().y << endl;

        window.display();
    }

    return 0;
}