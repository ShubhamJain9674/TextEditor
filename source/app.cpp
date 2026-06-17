#include "app.h"

App::App()
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


}

App::~App()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void App::Run()
{

    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}



