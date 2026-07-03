#include "App.h"

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

    fontManager = std::make_unique<FontManager>();

    //testing text input

    textArea = std::make_unique<TextArea>(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,renderer,*fontManager);

    SDL_StartTextInput(window);


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
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                {
                    running = false;
                    break;
                }

                case SDL_EVENT_KEY_DOWN:
                {
                    if(event.key.key == SDLK_BACKSPACE )
                        textArea->DeleteBeforeCursor();

                    else if(event.key.key == SDLK_RETURN )
                        textArea->InsertNewLine();

                    break;
                }

                case SDL_EVENT_TEXT_INPUT:
                {
                    size_t lastIndex = std::strlen(event.text.text) - 1;
                    textArea->AddChar(event.text.text[lastIndex]);
                    break;
                }
            }
        }

        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        textArea->Update(w,h);

        Render();
    }
}

void App::Render()
{

    SDL_SetRenderDrawColor(renderer,bgColor.r,bgColor.g,bgColor.b,bgColor.a);
    SDL_RenderClear(renderer);

    textArea->Render();

    SDL_RenderPresent(renderer);

}
