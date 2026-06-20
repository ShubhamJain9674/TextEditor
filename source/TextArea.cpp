#include "TextArea.h"

TextArea::TextArea(float x,float y,float w,float h,SDL_Renderer* renderer)
{
    rect = { x, y, w, h };
    this->renderer = renderer;

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        // return SDL_APP_FAILURE;
        return;
    }

    font = TTF_OpenFont("Roboto_Condensed-Black.ttf", fontSize);
    if (!font) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return;
    }

}

void TextArea::addChar(char ch)
{
    text += ch;
    SDL_Log(text.c_str());
}

void TextArea::update(int w,int h)
{
    // recalibrate dims
    rect.w = w;
    rect.h = h;
}

void TextArea::render()
{

    Uint8 r,g,b,a;

    SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);


    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderRect(renderer,&rect);
    int posx = textAreaStart + padx;
    int posy = textAreaStart + pady;
    for(size_t i = 0; i < text.size(); i++)
    {
        SDL_Texture* tex = getCharacterTexture(text[i]);

        if(tex)
        {
            SDL_FRect charRect;

            SDL_GetTextureSize(tex,&charRect.w,&charRect.h);

            if( (posx + charRect.w) >= (rect.w - padx) ){
                posx = textAreaStart;
                posy+= charRect.h;
            }
            else
                posx += charRect.w;

            charRect.x = posx;
            charRect.y = posy;

            SDL_RenderTexture(renderer, tex,NULL,&charRect);
        }
    }
    SDL_SetRenderDrawColor(renderer,r,g,b,a);

}

SDL_Texture* TextArea::getCharacterTexture(char ch)
{

    if(glyphCache.find(ch) == glyphCache.end())
    {
        SDL_Texture *glTexture = nullptr;
        char temp[2] = { ch, '\0' };

        SDL_Surface *txtSurface = TTF_RenderText_Blended(this->font,temp, 0, txtColor);
        if (txtSurface) {
            glTexture = SDL_CreateTextureFromSurface(renderer, txtSurface);
            SDL_DestroySurface(txtSurface);
        }
        if (!glTexture) {
            SDL_Log("Couldn't create text: %s\n", SDL_GetError());
            // return SDL_APP_FAILURE;
            return nullptr;
        }
        glyphCache[ch] = glTexture;
        return glTexture;
    }
    else
        return glyphCache[ch];
}
