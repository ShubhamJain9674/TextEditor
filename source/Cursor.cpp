#include "Cursor.hpp"


void Cursor::Update(float dt,const GapBuffer& buffer)
{

    // update index
    int pos = buffer.GetCursorPos();
    if(pos <=0 )
        index = 0;
    index = pos;

    // update dt
    time += dt;
    if(time >= 2 * blinkRate)
    {
        time = 0.0f;
        color.a = 255;
    }
    else if(time >= blinkRate)
    {
        color.a = 0;
    }
}


void Cursor::Draw(SDL_Renderer* renderer,float x,float y)
{
    if(renderer == nullptr)
        return;

    // desired width and height.
    float h = fontManager.GetFontHeight();
    float w = cursorWidth;

    // Get original renderer color
    Uint8 r,g,b,a;
    SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);

    // draw cursor
    SDL_FRect rect = { x,y,w,h };
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
    SDL_RenderFillRect(renderer,&rect);

    // restore original color.
    SDL_SetRenderDrawColor(renderer,r,g,b,a);

}

void Cursor::SetCursorBlinkRate(float rate) {
    if(rate > 0.0f)
        blinkRate = rate;
}
