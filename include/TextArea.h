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

    void HandleCharEntry(const Command& c);

    void HandleCharDelBack(const Command& c);

    void HandleCharDelForw(const Command& c);

    void HandleCurMovLeft(const Command& c);

    void HandleCurMovRight(const Command& c);

    void HandleCurMovUp(const Command& c);

    void HandleCurMovDown(const Command& c);

    void HandleMouseClick(const Command& c);

private:

    const FontManager& fontManager;
    GapBuffer buffer;
    Cursor cursor;

};

