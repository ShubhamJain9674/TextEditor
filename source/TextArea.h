#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>


/*
This class will hold all functionality of Text area such as
- mantaining data structure for text
- scrolling functionality.
- Cursor management
- Rendering text.
*/
class TextArea
{
public:
    TextArea(int x,int y,int w,int h,SDL_Renderer* renderer);

    void update(int w,int h);

private:
    SDL_FRect m_rect;
    SDL_Renderer* m_renderer;

    Uint16 m_font_size = 18;




    //placeholder string;

    SDL_Texture *m_txt_texture = nullptr;
    TTF_Font* m_font = nullptr;
    SDL_Color m_txt_color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    SDL_Surface *m_txt_surface;
};
