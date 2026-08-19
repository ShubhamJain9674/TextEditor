#pragma once
#include "GapBuffer.h"
#include "FontManager.h"
#include <SDL3/SDL.h>


class Cursor
{
public:
    Cursor(const FontManager& fm)
        :fontManager(fm){}

    int GetCursorIndex()const { return index; }

    void Update(float dt,const GapBuffer& buffer); // index updated via buffer and dt for animation

    void Draw(SDL_Renderer* renderer,float x,float y);  // when and where decided by Textarea renderer.

    void SetCursorColor(SDL_Color color) { this->color = color; }
    void SetCursorBlinkRate(float rate);
    void SetCursorWidth(float width) { cursorWidth = width; }


private:
    const FontManager& fontManager;

    int index { 0 };

    float blinkRate { 0.75f };
    float cursorWidth { 1.0f };
    SDL_Color color { 255,255,255,255 };


    // for anim
    float time {0.0f};
};
