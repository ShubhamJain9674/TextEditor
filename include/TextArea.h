#pragma once
#include "GapBuffer.h"
#include "Cursor.hpp"
#include "Focusable.hpp"



class TextArea : public IFocusable
{
public:
    TextArea(const FontManager& fm,SDL_FRect rect);
    ~TextArea() = default;


    // void OnFocused()override;
    // void OnUnfocused()override;

    std::string GetName()override { return "TextArea"; }

    void HandleCommands(const std::vector<Command>& commands)override;
    void Update(float dt,SDL_FRect);

private:
    const FontManager& fontManager;
    GapBuffer buffer;
    Cursor cursor;

};

