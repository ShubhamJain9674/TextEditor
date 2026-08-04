#include "InputManager.hpp"
#include <cstring>

//TODO : drag select , shift select


Command InputManager::HandleEvent(SDL_Event event)
{
    Command c;
    switch(event.type)
    {
        // needs to be before text input to consume kmods.
        case SDL_EVENT_KEY_DOWN:
        {
            auto key = event.key;
            c = HandleKeyPress(key);
            break;
        }
        case SDL_EVENT_TEXT_INPUT :
        {
            c.type = CommandType::KEYBOARD_CHARACTER_ENTRY;
            size_t lastIndex = std::strlen(event.text.text) - 1;
            c.key  = event.text.text[lastIndex];
            break;
        }
        // currently only leftclick.
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            if(event.button.down
                && event.button.button == 1)
            {
                c.type = CommandType::MOUSE_CLICK;
                c.mouseX = event.button.x;
                c.mouseY = event.button.y;
            }
            break;
        }
        default:
            break;
    }
    return c;
}



Command InputManager::HandleKeyPress(SDL_KeyboardEvent key)
{
    Command c;

    switch(key.scancode)
    {
        case SDL_SCANCODE_C:
        {
            if(key.mod & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL))
            {
                c.type = CommandType::COPY;
            }
            break;
        }
        case SDL_SCANCODE_X:
        {
            if(key.mod & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL))
            {
                c.type = CommandType::CUT;
            }
            break;
        }
        case SDL_SCANCODE_V:
        {
            if(key.mod & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL))
            {
                c.type = CommandType::PASTE;
            }
            break;
        }
        case SDL_SCANCODE_Z:
        {
            if(key.mod & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL))
            {
                c.type = CommandType::UNDO;
            }
            break;
        }
        case SDL_SCANCODE_Y:
        {
            if(key.mod & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL))
            {
                c.type = CommandType::REDO;
            }
            break;
        }
        case SDL_SCANCODE_UP:
        {
            c.type = CommandType::CURSOR_MOVE_UP;
            break;
        }
        case SDL_SCANCODE_DOWN:
        {
            c.type = CommandType::CURSOR_MOVE_DOWN;
            break;
        }
        case SDL_SCANCODE_LEFT:
        {
            c.type = CommandType::CURSOR_MOVE_LEFT;
            break;
        }
        case SDL_SCANCODE_RIGHT:
        {
            c.type = CommandType::CURSOR_MOVE_RIGHT;
            break;
        }
        case SDL_SCANCODE_DELETE:
        {
            c.type = CommandType::DELETE_FORWARD;
            break;
        }
        case SDL_SCANCODE_BACKSPACE:
        {
            c.type = CommandType::DELETE_BACK;
            break;
        }
        default:
            break;
    }
    return c;
}

