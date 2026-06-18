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


    //testing text input
    // textArea = new TextArea(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,renderer);
    textArea = std::make_unique<TextArea>(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,renderer);

    SDL_StartTextInput(window);

}

App::~App()
{
    SDL_StopTextInput(window); //temp
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void App::run()
{


    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if(event.type == SDL_EVENT_TEXT_INPUT)
            {
                // handleInput();
            }
        }

        render();
    }
}

void App::render()
{

    SDL_SetRenderDrawColor(renderer,bgColor.r,bgColor.g,bgColor.b,bgColor.a);
    SDL_RenderClear(renderer);

    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    textArea->update(w,h);

    SDL_RenderPresent(renderer);

}
