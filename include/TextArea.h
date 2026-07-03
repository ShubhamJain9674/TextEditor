#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "GapBuffer.h"
#include "FontManager.h"

/*
This class will hold all functionality of Text area such as
- mantaining data structure for text
- scrolling functionality.
- Cursor management
- Rendering text.
*/

class Cursor
{
};


class Line
{
};



class TextArea
{

    // note using char as glyph cache instead of custom data structure for simplicity.
    // repopulate glyph cache on change of attributes like size font etc.
    // otherwise requires a seperate data structure to mantain cache holding all the properties

    GapBuffer textBuffer;
    //placeholder string holding the text;
};


// implementing  a line
// for each line store a vector of position of each character
// from glyph texture / font texture get the height of the line or set it to maximum possible for that font
// on click from the y coordinate get the line where the text reside
// from the x coordinate do a binary search to closest two indices and set the cursor to glyph start.


// A line class
// each line stores a line goal
// vector containing cursor x pos for each glyph for estimate cursor pos on click.



