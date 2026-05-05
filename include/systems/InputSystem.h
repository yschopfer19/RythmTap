#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "InputTypes.h"

using namespace std;
using namespace sf;

class InputSystem
{
public:
    void handleEvent(const Event &event);

    vector<InputEvent> pollInputs();

private:
    vector<InputEvent> events;

    void handleKey(Keyboard::Scancode code, InputAction action);
};