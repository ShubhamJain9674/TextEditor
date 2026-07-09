#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include "GapBuffer.h"
#include "FontManager.h"

class Cursor;

class Line;


class TextArea
{

    // note using char as glyph cache instead of custom data structure for simplicity.
    // repopulate glyph cache on change of attributes like size font etc.
    // otherwise requires a seperate data structure to mantain cache holding all the properties
public:
    TextArea(SDL_Renderer* renderer,FontManager& fm,SDL_FRect rect);

    void Update(int width,int height,float dt);
    void Update(SDL_FRect newRect,float dt);

    SDL_FRect GetRect()const { return rect; }
    const Line* GetLine(size_t index)const;

#ifndef NDEBUG
    void RenderDebug();
#endif


    void GetTextStartCoord(float* x,float* y) const;
    void InsertLineAtEnd();

    int GetFontHeight() const { return fontManager.GetFontHeight(); }


private:

    SDL_Renderer* renderer;
    FontManager& fontManager;
    SDL_FRect rect;

    std::unique_ptr<Cursor> cursor;

    std::unique_ptr<GapBuffer> textBuffer;

    std::vector<std::unique_ptr<Line>> lines;


    float boundaryMarginX = 1.0f;
    float boundaryMarginY = 1.0f;




};



class Line
{
public:
    Line(const TextArea& textArea,SDL_Renderer* renderer,int lineNo);

    void Update(float dt);
    void GetLineEndCoordinates(float* x,float* y)const;

    #ifndef NDEBUG

    void RenderDebug();

    #endif

private:

    const TextArea&  textArea;
    SDL_Renderer*    renderer;
    int              lineNo;
    SDL_FRect        rect;


    std::vector<int> cursorPosXHistory;
    int targetIndex {0};

    float linePadx = 3.0f;


};


class Cursor
{
public:
    Cursor(SDL_Renderer* renderer,const TextArea& textArea);

#ifndef NDEBUG
    void RenderDebug();
#endif

    void Update(float dt);

private:
    SDL_Renderer* renderer;
    const TextArea& textArea;

    SDL_FRect rect;

    int bufferIndex{0};
    int lineIndex{0};
    int lineNo{0};

    float cursorWidth = 2.0f;
    float cursorHeightFactor = 0.90f;

    //cursor animation
    float animTime = 0.0f;
    float blinkTime = 0.5f;
    SDL_Color cursorColor = {0 ,255,255,255 };
    Uint8 cursorAlpha = 255;



};


// implementing  a line
// for each line store a vector of position of each character
// from glyph texture / font texture get the height of the line or set it to maximum possible for that font
// on click from the y coordinate get the line where the text reside
// from the x coordinate do a binary search to closest two indices and set the cursor to glyph start.


// A line class
// each line stores a line goal
// vector containing cursor x pos for each glyph for estimate cursor pos on click.



