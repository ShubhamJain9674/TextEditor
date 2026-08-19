#include "TextArea.h"


TextArea::TextArea(const FontManager& fm,SDL_FRect)
    :IFocusable(rect),fontManager(fm),cursor(fm)
{

}


void TextArea::Update(float dt,SDL_FRect rect)
{
    this->rect = rect;
    cursor.Update(dt,buffer);
    buffer.DisplayContent();
}



void TextArea::HandleCharEntry(const Command& c)
{
    buffer.InsertAtCursor(c.key);
}

void TextArea::HandleCharDelBack(const Command& c)
{
    buffer.DeleteBeforeCursor();
}

void TextArea::HandleCharDelForw(const Command& c)
{
    buffer.DeleteAfterCursor();
}

void TextArea::HandleCurMovLeft(const Command& c)
{
    buffer.MoveCursor(BUFFER_CURSOR_MOVE_LEFT,1);
}

void TextArea::HandleCurMovRight(const Command& c)
{
    buffer.MoveCursor(BUFFER_CURSOR_MOVE_RIGHT,1);
}

void TextArea::HandleCurMovUp(const Command& c)
{
 // TODO
 // jump to prev line this info might be stored in line metadata.

}

void TextArea::HandleCurMovDown(const Command& c)
{
  // TODO
    // jump to next line this info might be stored in line metadata.

}

void TextArea::HandleMouseClick(const Command& c)
{
  // TODO
  // move to the pos of click.
}




void TextArea::HandleCommands(const std::vector<Command>& commands)
{
    // std::cout << "hello from textArea" << std::endl;

    if(commands.size() == 0)
        return;

    for(auto command : commands)
    {
        switch(command.type)
        {
            case CommandType::KEYBOARD_CHARACTER_ENTRY:
            {
                HandleCharEntry(command);
                break;
            }
            case CommandType::DELETE_BACK:
            {
                HandleCharDelBack(command);
                break;
            }
            case CommandType::DELETE_FORWARD:
            {
                HandleCharDelForw(command);
                break;
            }
            case CommandType::CURSOR_MOVE_LEFT:
            {
                HandleCurMovLeft(command);
                break;
            }
            case CommandType::CURSOR_MOVE_RIGHT:
            {
                HandleCurMovRight(command);
                break;
            }
            case CommandType::CURSOR_MOVE_UP:
            {
                HandleCurMovUp(command);
                break;
            }
            case CommandType::CURSOR_MOVE_DOWN:
            {
                HandleCurMovDown(command);
                break;
            }
            case CommandType::MOUSE_CLICK:
            {
                HandleMouseClick(command);
                break;
            }
            default:
                break;

        }
    }
}

