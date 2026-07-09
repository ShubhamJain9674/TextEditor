
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <memory>
#include <cstring>


#include "FontManager.h"
#include "TextArea.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class App
{
public:
    App();
    ~App();

    void Run();
    void Render();


private:
    void UpdateDeltaTime();


private:

    bool running = true;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;


    std::unique_ptr<FontManager> fontManager;
    std::unique_ptr<TextArea> textArea;
    SDL_Color bgColor = { 0,0,0,255 };


    float dt { 0.0f };
    Uint64 lastRecordedTime = 0;

};



