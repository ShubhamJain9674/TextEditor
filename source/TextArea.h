#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>
#include <string>

/*
This class will hold all functionality of Text area such as
- mantaining data structure for text
- scrolling functionality.
- Cursor management
- Rendering text.
*/
class TextArea
{
public:
    TextArea(float x,float y,float w,float h,SDL_Renderer* renderer);

    void update(int w,int h,const char* txt);
    void render();

private:
    SDL_Texture* getCharacterTexture(char ch);


private:
    SDL_FRect rect;
    SDL_Renderer* renderer;

    int fontSize = 18;


    TTF_Font* font = nullptr;
    SDL_Color txtColor = { 255, 255, 255, SDL_ALPHA_OPAQUE };


    // note using char as glyph cache instead of custom data structure for simplicity.
    // repopulate glyph cache on change of attributes like size font etc.
    // otherwise requires a seperate data structure to mantain cache holding all the properties


    std::unordered_map<char,SDL_Texture*> glyphCache;

    //placeholder string holding the text;
    std::string text;

};



