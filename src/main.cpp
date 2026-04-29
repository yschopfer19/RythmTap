#include <iostream>
#include <SFML/Graphics.hpp>

#include "Lane.h"
#include "Note.h"

using namespace std;
using namespace sf;

string checkTiming(Note& note, float NoteY, float hitzoneY, int lane_index)
{   
    if (note.getlaneIndex() == lane_index)
    {   
        float distance = abs(NoteY - hitzoneY); 
        if (distance < 10)
        {
            cout << "Perfect!";
            return "Perfect!";
        }
        else if (distance < 30)
        {
            cout << "Good!";
            return "Good!";
        }
        else
        {
            cout << "Miss!";
            return "Miss!";
        } 
    }
    cout << "Miss!";
    return "Miss!";
}

int main()
{
    RenderWindow window(VideoMode({800, 600}), "Rhythm Game");

    //Optionen für später 
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    Lane lanes[] = { 
        Lane(50, 100, 100, 200, Color::White, Color::Yellow),
        Lane(250, 100, 100, 200, Color::White, Color::Yellow),
        Lane(450, 100, 100, 200, Color::White, Color::Yellow),
        Lane(650, 100, 100, 200, Color::White, Color::Yellow)
    };

    Note note = Note(50, 100, 100, 20, Color::Red, 50, 0);

    Clock clock;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (auto* keyEvent = event->getIf<Event::KeyPressed>())
            {
                switch (keyEvent->scancode)
                {
                    case Keyboard::Scancode::D: checkTiming(note, lanes[0].getHitzonePosition().y, note.getPosition().y, 0); break; 
                    case Keyboard::Scancode::F: checkTiming(note, lanes[1].getHitzonePosition().y, note.getPosition().y, 1); break; 
                    case Keyboard::Scancode::J: checkTiming(note, lanes[2].getHitzonePosition().y, note.getPosition().y, 2); break; 
                    case Keyboard::Scancode::K: checkTiming(note, lanes[3].getHitzonePosition().y, note.getPosition().y, 3 ); break; 
                }
            }

            if (event->is<Event::Closed>())
                window.close();
        }
        
        Time time = clock.restart();
        float deltatime = time.asSeconds();

        window.clear(Color::Black);
        
        for (const Lane& lane : lanes) {
            lane.draw(window);
        }

        note.update(deltatime);
        note.draw(window);
        //cout << note.getPosition().y << endl;
        
        window.display();
    }

    return 0;
}