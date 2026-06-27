#include "TextArea.h"

TextArea::TextArea(float x,float y,float w,float h,SDL_Renderer* renderer,FontManager& fm)
                    :fontManager(fm)
{
    rect = { x, y, w, h };
    this->renderer = renderer;

}

void TextArea::AddChar(char ch)
{
    textBuffer.InsertAtCursor(ch);
    SDL_Log(textBuffer.ToString().c_str());
}

void TextArea::Update(int w,int h)
{
    // recalibrate dims
    rect.w = w;
    rect.h = h;
}

void TextArea::Render()
{

    Uint8 r,g,b,a;

    SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);


    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderRect(renderer,&rect);
    int posx = textAreaStart + padx;
    int posy = textAreaStart + pady;

    std::string text = textBuffer.ToString();     // seems quite expensive to hold a quite lot of text to render . may be gapbuffer should
    // have  a function to stream text
    // NOTE : std::string doesnt use stack internally , it still expensive to return the whole thing and should implement a streaming window


    for(size_t i = 0; i < text.size(); i++)
    {
        SDL_Texture* tex = GetCharacterTexture(text[i]);

        if(tex)
        {
            SDL_FRect charRect;
            SDL_GetTextureSize(tex,&charRect.w,&charRect.h);
            charRect.x = posx;
            charRect.y = posy;
            SDL_RenderTexture(renderer, tex,NULL,&charRect);


            if( (posx + charRect.w) >= textAreaStart + (rect.w - padx) ){
                posx = textAreaStart;
                posy = (linePadding > charRect.h)? linePadding : charRect.h;
            }
            else
                posx += charRect.w + charSpacing;


        }
    }
    SDL_SetRenderDrawColor(renderer,r,g,b,a);

}

SDL_Texture* TextArea::GetCharacterTexture(char ch)
{
    return fontManager.GetCharacterTexture(ch,renderer,txtColor);
}
