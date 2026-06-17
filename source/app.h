
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class App
{
public:
    App();
    ~App();

    void Run();

private:
    bool running = true;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};
