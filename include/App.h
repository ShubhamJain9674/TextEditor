
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>


#include <memory>
#include <cstring>

#include "Command.hpp"
#include "FontManager.h"
#include "TextArea.h"
#include "InputManager.hpp"
#include "FocusManager.hpp"
#include "InputDispatcher.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class App : public IFocusable
{
public:
    App();
    ~App();

    void Run();
    void Update();
    void Render();

    void HandleCommands(const std::vector<Command>& commands)override;

    // void OnFocused()override;
    // void OnUnfocused()override;

    std::string GetName()override { return "APP"; }


private:
    void UpdateDeltaTime();


private:


    InputDispatcher inputDispatcher;
    InputManager input;
    FocusManager focus;


    bool running = true;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;


    std::unique_ptr<FontManager> fontManager;
    SDL_Color bgColor = { 0,0,0,255 };


    float dt { 0.0f };
    Uint64 lastRecordedTime = 0;



};



