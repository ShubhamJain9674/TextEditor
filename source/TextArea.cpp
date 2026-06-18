#include "TextArea.h"

TextArea::TextArea(int x,int y,int w,int h,SDL_Renderer* renderer)
{
    m_rect = { x, y, w, h };
    m_renderer = renderer;
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        // return SDL_APP_FAILURE;
        return;
    }

    TTF_Font *m_font = TTF_OpenFont("Roboto_Condensed-Black.ttf", m_font_size);
    if (!m_font) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return;
    }


    m_txt_surface = TTF_RenderText_Blended(m_font,"Hello world", 0, m_txt_color);
    if (m_txt_surface) {
        m_txt_texture = SDL_CreateTextureFromSurface(m_renderer, m_txt_surface);
        SDL_DestroySurface(m_txt_surface);
    }

    if (!m_txt_texture) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
        // return SDL_APP_FAILURE;
        return;
    }

}

void TextArea::update(int w,int h)
{
    // recalibrate dims
    m_rect.w = w;
    m_rect.h = h;


    Uint8 r,g,b,a;

    SDL_GetRenderDrawColor(m_renderer,&r,&g,&b,&a);


    SDL_SetRenderDrawColor(m_renderer,255,255,255,255);
    SDL_RenderRect(m_renderer,&m_rect);
    // SDL_RenderTexture(m_renderer, m_txt_texture, NULL, NULL);
    SDL_SetRenderDrawColor(m_renderer,r,g,b,a);

}
