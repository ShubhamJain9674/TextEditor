#pragma once
#include <vector>
#include <string>

enum class CommandType
{
    MOUSE_CLICK,
    MOUSE_DRAG,
    KEYBOARD_CHARACTER_ENTRY,
    CURSOR_MOVE_LEFT,
    CURSOR_MOVE_RIGHT,
    CURSOR_MOVE_UP,
    CURSOR_MOVE_DOWN,
    DELETE_BACK,
    DELETE_FORWARD,
    COPY,
    CUT,
    PASTE,
    UNDO,
    REDO,
    Count
};


struct Command
{
    CommandType type;

    char key;                  // Keyboard character

    int mouseX;               // Mouse Click coordinates
    int mouseY;

    static const char* ToString(Command command)
    {
        switch(command.type)
        {
            case CommandType::MOUSE_CLICK : return "MOUSE_CLICK"; break;
            case CommandType::MOUSE_DRAG : return "MOUSE_DRAG"; break;
            case CommandType::KEYBOARD_CHARACTER_ENTRY : return "KEYBOARD_CHARACTER_ENTRY"; break;
            case CommandType::CURSOR_MOVE_LEFT : return "CURSOR_MOVE_LEFT"; break;
            case CommandType::CURSOR_MOVE_RIGHT : return "CURSOR_MOVE_RIGHT"; break;
            case CommandType::CURSOR_MOVE_UP : return "CURSOR_MOVE_UP"; break;
            case CommandType::CURSOR_MOVE_DOWN : return "CURSOR_MOVE_DOWN"; break;
            case CommandType::DELETE_BACK : return "DELETE_BACK"; break;
            case CommandType::DELETE_FORWARD : return "DELETE_FORWARD"; break;
            case CommandType::COPY: return "COPY"; break;
            case CommandType::CUT : return "CUT"; break;
            case CommandType::PASTE : return "PASTE"; break;
            case CommandType::UNDO : return "UNDO"; break;
            case CommandType::REDO : return "REDO"; break;
            default:
                break;

        }
        return "";
    }

};


class ICommandHandler
{
public:
    virtual void HandleCommands(const std::vector<Command>& commands) = 0;
};
