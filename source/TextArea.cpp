#include "TextArea.h"

TextArea::TextArea(const FontManager& fm,SDL_FRect)
    :IFocusable(rect),fontManager(fm),cursor(fm)
{

}


void TextArea::Update(float dt,SDL_FRect rect)
{
    this->rect = rect;
    cursor.Update(dt,buffer);

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
                buffer.InsertAtCursor(command.key);
                break;
            }
            case CommandType::MOUSE_CLICK:
            {
                break;
            }
            default:
                break;

        }


    }
}

