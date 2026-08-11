#include "App.h"
#include <iostream> // TODO


App::App()
    :inputDispatcher(*this)
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL init failed");
    }


    window = SDL_CreateWindow("TextEditor",WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window,nullptr);

    if(window == nullptr)
    {
        SDL_Log("Window creation failed!");
        running  = false;
    }

    fontManager = std::make_unique<FontManager>();

    //testing text input
    SDL_FRect textRect = { .0f ,.0f ,WINDOW_WIDTH,WINDOW_HEIGHT };

    SDL_StartTextInput(window);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);



}

App::~App()
{
    SDL_StopTextInput(window); //temp
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void App::Run()
{
    while(running)
    {
        Update();
        Render();
    }
}

void App::Update()
{
    UpdateDeltaTime();

    SDL_Event event;
    std::vector<Command> commands;

    while(SDL_PollEvent(&event))
    {
        commands.push_back(input.HandleEvent(event));


        switch(event.type)
        {
            case SDL_EVENT_QUIT:
            {
                running = false;
                break;
            }
        }
    }
    focus.Update(commands);
    inputDispatcher.Dispatch(focus.GetCurrentlyFocused(),commands);

}

void App::Render()
{

    SDL_SetRenderDrawColor(renderer,bgColor.r,bgColor.g,bgColor.b,bgColor.a);
    SDL_RenderClear(renderer);


    SDL_RenderPresent(renderer);

}

void App::UpdateDeltaTime()
{
    Uint64 now = SDL_GetTicks();
    dt = (now - lastRecordedTime) / 1000.0f;

    lastRecordedTime = now;
}

void App::HandleCommands(const std::vector<Command>& commands)
{
    // TODO
}

