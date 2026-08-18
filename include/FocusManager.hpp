#pragma once
#include "Focusable.hpp"

class FocusManager
{

public:

    FocusManager(IFocusable* defaultElement)
        :defaultElement(defaultElement),currentlyFocused(defaultElement){}

    void Update(std::vector<Command>& commands);

    void addElement(IFocusable* element);

    void removeElement(IFocusable* element);

    IFocusable* GetCurrentlyFocused() const { return currentlyFocused; }

private:
    IFocusable* GetUnderMouseElement(float mouseX,float mouseY);
    void HandleFocusChange(IFocusable* newFocused);

private:
    IFocusable* const defaultElement { nullptr };
    IFocusable* currentlyFocused { nullptr };
    std::vector<IFocusable*> focusableList;
};
