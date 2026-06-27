#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>
#include <string>
#include "GapBuffer.h"
#include "FontManager.h"


/*
This class will hold all functionality of Text area such as
- mantaining data structure for text
- scrolling functionality.
- Cursor management
- Rendering text.
*/

struct Cursor
{
    int index;
    int BufferIndex;
    int goalColumn;
};



class TextArea
{
public:
    TextArea(float x,float y,float w,float h,SDL_Renderer* renderer,FontManager& fm);

    void Update(int w,int h);
    void AddChar(char ch);
    void DeleteBeforeCursor();
    void Render();

private:
    SDL_Texture* GetCharacterTexture(char ch);



private:

    SDL_FRect rect;
    SDL_Renderer* renderer;
    FontManager& fontManager;






    // text formatting attributes:-

    Uint16 padx = 10;     // boundary padding x
    Uint16 pady = 10;     // boundary padding y


    SDL_Color   txtColor      = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    float       charSpacing   = 0.75f;                                      // inter character spacing.
    float       linePadding   = 0.5f;                                       // inter line spacing


    // Editor setup attributes
    const Uint16 textAreaStart = 0;

    Cursor cusor { 0,0,0 };



    // note using char as glyph cache instead of custom data structure for simplicity.
    // repopulate glyph cache on change of attributes like size font etc.
    // otherwise requires a seperate data structure to mantain cache holding all the properties


    std::unordered_map<char,SDL_Texture*> glyphCache;

    GapBuffer textBuffer;
    //placeholder string holding the text;



};


// implementing  a line
// for each line store a vector of position of each character
// from glyph texture / font texture get the height of the line or set it to maximum possible for that font
// on click from the y coordinate get the line where the text reside
// from the x coordinate do a binary search to closest two indices and set the cursor to glyph start.





