#include "FocusManager.hpp"
#include <algorithm>

// TODO : currently i am not consuming the click
//  should the input in a frame contain multiple clicks
// if its consumed what happens to other clicks ?

void FocusManager::Update(std::vector<Command>& commands)
{
    // handles only the latest mouse click event.

    for(int i = commands.size() - 1; i >=0 ; --i )
    {
        if(commands[i].type == CommandType::MOUSE_CLICK)
        {
            auto c = commands[i];
            currentlyFocused = GetUnderMouseElement(c.mouseX,c.mouseY);
            break;
        }
    }
}


IFocusable* FocusManager::GetUnderMouseElement(float mouseX,float mouseY)
{

    for(auto i : focusableList)
    {
        if(i && i->IsUnderMouse(mouseX,mouseY))
            return i;
    }
    return nullptr;
}

void FocusManager::addElement(IFocusable* element)
{
    if(element)
        focusableList.push_back(element);
}

void FocusManager::removeElement(IFocusable* element)
{
    focusableList.erase(
        std::remove(
            focusableList.begin(),
            focusableList.end(),
            element
        ),
        focusableList.end()
    );
}

