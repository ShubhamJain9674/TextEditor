#include "TextArea.h"




//TextArea

TextArea::TextArea(SDL_Renderer* renderer,FontManager& fm,SDL_FRect rect)
                    :renderer(renderer),fontManager(fm),rect(rect)
{
    textBuffer = std::make_unique<GapBuffer>();

    // FirstLine
    InsertLine();


}

void TextArea::Update(int width,int height)
{
    rect.w = width;
    rect.h = height;
}


void TextArea::RenderDebug()
{
    Uint8 r,g,b,a;

    SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderRect(renderer,&rect);
    SDL_SetRenderDrawColor(renderer,r,g,b,a);

    for(auto& line : lines)
    {
        line->RenderDebug();
    }

}

void TextArea::InsertLine()
{
    float x,y;
    GetTextStartCoord(&x,&y);
    SDL_FRect lineRect = {x,y,
                        rect.w,
                        static_cast<float>(fontManager.GetFontHeight())
    };

    lines.push_back(std::make_unique<Line>(lineRect,renderer));
}


void TextArea::GetTextStartCoord(float* x,float* y)
{
    *x = rect.x + boundaryMarginX;
    *y = rect.y + boundaryMarginY;
}

//Line

Line::Line(SDL_FRect rect,SDL_Renderer* renderer)
    :rect(rect),renderer(renderer)
{
    cursorPosXHistory.push_back(rect.x);
}



void Line::RenderDebug()
{
    Uint8 r,g,b,a;

    SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderRect(renderer,&rect);
    SDL_SetRenderDrawColor(renderer,r,g,b,a);
}


