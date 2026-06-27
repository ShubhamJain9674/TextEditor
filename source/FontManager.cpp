#include "FontManager.h"

namespace fs = std::filesystem;


FontManager::FontManager()
{

    // getting font files.

    fs::path p = GetFontDirPath();

    if(!fs::exists(p))
    {
        // handle by either using system fonts or throwing an error.
    }
    else
    {

        for(const auto& dirEntry : fs::directory_iterator{p})
        {
            if(!is_regular_file(dirEntry))
                continue;

            auto filePath = dirEntry.path();
            if(filePath.extension() == ".ttf" || filePath == ".TTF")
            {
                fonts.push_back(filePath.stem());
            }
        }


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
