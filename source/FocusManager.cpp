#include "FocusManager.hpp"
#include <algorithm>
#include <cassert>



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
            auto clickedElement = GetUnderMouseElement(c.mouseX,c.mouseY);
            HandleFocusChange(clickedElement);
            break;

        }
    }
}

void FocusManager::HandleFocusChange(IFocusable* clickedElement)
{
    if(clickedElement == defaultElement)   // (NOTE) this was to handle the state where app will nest elements under it
        return;                            // you can focus element under apps and avoid focusing both
                                           // (TODO) but elements can have nested elemnent themself
                                           // should you focus both or focus the inner element.
    assert(defaultElement != nullptr);
    if(!clickedElement)
        clickedElement = defaultElement;

    assert(clickedElement != nullptr);
    assert(currentlyFocused != nullptr);


    if(clickedElement != currentlyFocused)
    {
        currentlyFocused->OnUnfocused();
        clickedElement->OnFocused();
    }
    currentlyFocused = clickedElement;
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

