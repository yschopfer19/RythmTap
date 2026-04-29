#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Note 
{
public:
    Note(float x, float y, float width, float height, sf::Color color, int speed, int lane_Index, float spawn_time);
    
    void draw(RenderWindow& window) const;

    void update(float deltatime);    
    
    Vector2f getPosition() const;
    int getlaneIndex() const;

    void setgotHit(bool got_Hit);
    bool getgotHit() const;

    float getSpawnTime() const;

    bool getspawned() const;
    void setspawned(bool spawned);

private:
    RectangleShape shape;  
    Vector2f position; 
    int speed;
    int lane_Index;
    bool got_Hit = false;
    float spawn_time;
    bool spawned = false;
};