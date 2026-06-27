#include "FontManager.h"

namespace fs = std::filesystem;


FontManager::FontManager()
{


    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        // return SDL_APP_FAILURE;
        return;
    }

    // getting font files.

    fs::path fontDirPath = GetFontDirPath();

    if(!fs::exists(fontDirPath))
    {
        // handle by either using system fonts or throwing an error.
    }
    else
    {

        for(const auto& dirEntry : fs::directory_iterator{fontDirPath})
        {
            if(!is_regular_file(dirEntry))
                continue;

            auto filePath = dirEntry.path();
            if(filePath.extension() == ".ttf" || filePath == ".TTF")
            {
                availableFonts.push_back(filePath.stem());
            }
        }
        if(availableFonts.size() == 0)
        {
            // handle same way , either using system font or throwing an error
        }
        else
        {
            defaultFont = availableFonts[0];   // later might store and remember user's preference.
            fs::path currFontPath (FONT_DIR);
            currFontPath =  currFontPath / (defaultFont + ".ttf");
            currentFont = TTF_OpenFont(currFontPath.string().c_str(), fontSize);
        }
    }

    if (!currentFont) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return;
    }

}

FontManager::~FontManager()
{

}

fs::path FontManager::GetFontDirPath()
{
    fs::path p = GetExecutablePath();
    if(!fs::exists(p))
    {
        std::cout << "Failed to get executable path !" << std::endl;
        return {};
    }

    return (p / FONT_DIR);

}

SDL_Texture* FontManager::GetCharacterTexture(char ch,
                                              SDL_Renderer* renderer,
                                              SDL_Color txtColor = { 255, 255, 255, SDL_ALPHA_OPAQUE })
{


    if(currentFont == nullptr)
    {
        std::cout << "CurrentFont is not valid !" << std::endl;
        return nullptr;
    }
    if(renderer == nullptr)
    {
        std::cout << "Invalid Renderer" << std::endl;
        return nullptr;
    }

    if(glyphCache.find(ch) == glyphCache.end())
    {
        SDL_Texture *glTexture = nullptr;
        char temp[2] = { ch, '\0' };


        SDL_Surface *txtSurface = TTF_RenderText_Blended(currentFont,temp, 0, txtColor);
        if (txtSurface) {
            glTexture = SDL_CreateTextureFromSurface(renderer, txtSurface);
            SDL_DestroySurface(txtSurface);
        }
        if (!glTexture) {
            SDL_Log("Couldn't create text: %s\n", SDL_GetError());
            // return SDL_APP_FAILURE;
            return nullptr;
        }
        glyphCache[ch] = glTexture;
        return glTexture;
    }
    else
        return glyphCache[ch];
}

