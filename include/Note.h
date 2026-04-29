#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Note 
{
public:
    Note(float x, float y, float width, float height, sf::Color color, int speed, int lane_Index);
    
    void draw(RenderWindow& window) const;

    void update(float deltatime);    
    
    Vector2f getPosition() const;
    int getlaneIndex() const;


private:
    RectangleShape shape;  
    Vector2f position; 
    int speed;
    int lane_Index;
};