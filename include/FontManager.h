#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>

#include <string>
#include <vector>
#include <unordered_map>


#include "FileHandling.h"


#define FONT_DIR "fonts"

// NOTE : replace by custom logging
#include <iostream>


class FontManager
{

public:
    FontManager();
    ~FontManager();

    static std::filesystem::path GetFontDirPath();

    SDL_Texture* GetCharacterTexture(char ch,SDL_Renderer* renderer,SDL_Color);
    int GetFontHeight()const { return TTF_GetFontHeight(currentFont); }


private:

    std::vector<std::string> availableFonts;            // all the available fonts.
    std::string defaultFont;                            // default fallback font.

    TTF_Font* currentFont{};                            // currentFont in use.
    int       fontSize      = 24;



    std::unordered_map<char,SDL_Texture*> glyphCache;   // (NOTE)right now caching for a single size if the cache needs to support multiple size
                                                         // either hold multiple cache  --> doesnt seem practical
                                                         // create a structure that holds different character data like bold ,italic,size etc.
};




