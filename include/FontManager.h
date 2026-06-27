#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>

#include <string>
#include <vector>

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
private:
    std::vector<std::string> fonts;

};




