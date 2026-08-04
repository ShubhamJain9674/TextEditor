#pragma once
#include "Command.hpp"
#include <SDL3/SDL_events.h>




class InputManager
{
public:

    Command HandleEvent(SDL_Event event);
private:
    Command HandleKeyPress(SDL_KeyboardEvent key);
};
