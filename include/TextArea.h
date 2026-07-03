#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include "GapBuffer.h"
#include "FontManager.h"






class Line
{
public:
    Line(SDL_FRect rect,SDL_Renderer* renderer);

    void SetHeight(unsigned int h) { height = h;}

#ifndef NDEBUG

    void RenderDebug();

#endif

private:

    SDL_FRect rect;
    SDL_Renderer* renderer;

    std::vector<int> cursorPosXHistory;
    int targetIndex {0};
    int height;
};



class TextArea
{

    // note using char as glyph cache instead of custom data structure for simplicity.
    // repopulate glyph cache on change of attributes like size font etc.
    // otherwise requires a seperate data structure to mantain cache holding all the properties
public:
    TextArea(SDL_Renderer* renderer,FontManager& fm,SDL_FRect rect);

    void Update(int width,int height);


#ifndef NDEBUG
    void RenderDebug();
#endif


    void GetTextStartCoord(float* x,float* y);
    void InsertLine();


private:

    SDL_Renderer* renderer;
    FontManager& fontManager;
    SDL_FRect rect;
    std::unique_ptr<GapBuffer> textBuffer;

    std::vector<std::unique_ptr<Line>> lines;


    float boundaryMarginX = 0.1f;
    float boundaryMarginY = 0.1f;


};


// implementing  a line
// for each line store a vector of position of each character
// from glyph texture / font texture get the height of the line or set it to maximum possible for that font
// on click from the y coordinate get the line where the text reside
// from the x coordinate do a binary search to closest two indices and set the cursor to glyph start.


// A line class
// each line stores a line goal
// vector containing cursor x pos for each glyph for estimate cursor pos on click.



