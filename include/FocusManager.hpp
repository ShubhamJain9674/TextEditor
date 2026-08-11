#pragma once
#include "Focusable.hpp"

class FocusManager
{

public:
    FocusManager() = default;

    void Update(std::vector<Command>& commands);

    void addElement(IFocusable* element);

    void removeElement(IFocusable* element);

    IFocusable* GetCurrentlyFocused() const { return currentlyFocused; }

private:
    IFocusable* GetUnderMouseElement(float mouseX,float mouseY);

private:
    IFocusable* currentlyFocused { nullptr };
    std::vector<IFocusable*> focusableList;
};
