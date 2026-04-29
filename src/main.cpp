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
        if (note.getgotHit())
        {
            return "Miss!";
        }
        float distance = abs(NoteY - hitzoneY); 
        if (distance < 10)
        {
            note.setgotHit(true);
            return "Perfect!";
        }
        else if (distance < 30)
        {
            note.setgotHit(true);
            return "Good!";
        }
        else
        {    
            return "Miss!";
        } 
   }
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

    Note note = Note(50, 100, 100, 20, Color::Red, 50, 0, 1.0f);

    Clock clock;

    float gameTime = 0.0f;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (auto* keyEvent = event->getIf<Event::KeyPressed>())
            {
                switch (keyEvent->scancode)
                {
                    case Keyboard::Scancode::D: cout << checkTiming(note, lanes[0].getHitzonePosition().y, note.getPosition().y, 0); break; 
                    case Keyboard::Scancode::F: cout << checkTiming(note, lanes[1].getHitzonePosition().y, note.getPosition().y, 1); break; 
                    case Keyboard::Scancode::J: cout << checkTiming(note, lanes[2].getHitzonePosition().y, note.getPosition().y, 2); break; 
                    case Keyboard::Scancode::K: cout << checkTiming(note, lanes[3].getHitzonePosition().y, note.getPosition().y, 3 ); break; 
                }
            }

            if (event->is<Event::Closed>())
                window.close();
        }
        
        Time time = clock.restart();
        float deltatime = time.asSeconds();
        
        gameTime += deltatime;

        window.clear(Color::Black);
        
        for (const Lane& lane : lanes) {
            lane.draw(window);
        }

        if (!note.getspawned() && gameTime >= note.getSpawnTime())
        {
            note.setspawned(true);
        }

        if (note.getspawned()) 
        {
            note.update(deltatime);
            note.draw(window);
        }

        if (note.getgotHit())
        {
            note.setspawned(false);
        } 

        
        //cout << note.getPosition().y << endl;
        
        window.display();
    }

    return 0;
}