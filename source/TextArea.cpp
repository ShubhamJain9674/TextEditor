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

void TextArea::update(int w,int h,const char* txt)
{
    // recalibrate dims
    rect.w = w;
    rect.h = h;

    text+=txt;


}

void TextArea::render()
{

    Uint8 r,g,b,a;

    SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);


    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderRect(renderer,&rect);

    for(int i = 0; i < text.size(); i++)
    {
        SDL_Texture* tex = getCharacterTexture(text[i]);
        int posx = 10;
        int posy = 10;
        if(tex)
        {
            int w,h;
            SDL_FRect dest;
            float scalex,scaley;
            SDL_GetRenderScale(renderer,&scalex,&scaley);
            SDL_Log("%f %f",scalex,scaley);
            SDL_SetRenderScale(renderer,2.0f,2.0f);
            SDL_GetTextureSize(tex,&dest.w,&dest.h);

            dest.x = posx;
            dest.y = posy;
            posx += dest.w;

            if(posx == 1100){
                posx = 10;
                posy = dest.h;
            }

            SDL_RenderTexture(renderer, tex, NULL,NULL);
            SDL_SetRenderScale(renderer,scalex,scaley);

        }
    }
    SDL_SetRenderDrawColor(renderer,r,g,b,a);

}

SDL_Texture* TextArea::getCharacterTexture(char ch)
{

    if(glyphCache.find(ch) == glyphCache.end())
    {
        SDL_Texture *glTexture = nullptr;

        SDL_Surface *txtSurface = TTF_RenderText_Blended(this->font,text.c_str(), 0, txtColor);
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
