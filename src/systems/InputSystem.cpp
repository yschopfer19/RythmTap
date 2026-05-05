#include <iostream>
#include "InputSystem.h"

using namespace std;

void InputSystem::handleEvent(const sf::Event &event)
{
    if (auto *key = event.getIf<sf::Event::KeyPressed>())
    {
        handleKey(key->scancode, InputAction::Press);
    }

    if (auto *key = event.getIf<sf::Event::KeyReleased>())
    {
        handleKey(key->scancode, InputAction::Release);
    }
}

vector<InputEvent> InputSystem::pollInputs()
{
    auto result = events;
    events.clear();
    return result;
}

void InputSystem::handleKey(sf::Keyboard::Scancode code, InputAction action)
{
    switch (code)
    {
    case sf::Keyboard::Scancode::D:
        events.push_back({LaneIndex{0}, action});
        break;
    case sf::Keyboard::Scancode::F:
        events.push_back({LaneIndex{1}, action});
        break;
    case sf::Keyboard::Scancode::J:
        events.push_back({LaneIndex{2}, action});
        break;
    case sf::Keyboard::Scancode::K:
        events.push_back({LaneIndex{3}, action});
        break;
    default:
        break;
    }
}
