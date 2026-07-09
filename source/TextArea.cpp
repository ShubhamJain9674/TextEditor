#include "TextArea.h"




//TextArea

TextArea::TextArea(SDL_Renderer* renderer,FontManager& fm,SDL_FRect rect)
                    :renderer(renderer),fontManager(fm),rect(rect)
{
    textBuffer = std::make_unique<GapBuffer>();

    // FirstLine
    InsertLineAtEnd();
    cursor = std::make_unique<Cursor>(renderer,(*this));

}

void TextArea::Update(int width,int height,float dt)
{
    if(width <= 0.0f || height <= 0.0f)
        return;

    rect.w = width;
    rect.h = height;

    for(auto& line:lines)
        line->Update(dt);

    cursor->Update(dt);
}

void TextArea::Update(SDL_FRect newRect,float dt)
{
    if(newRect.w <= 0.0f || newRect.h <= 0.0f)
        return;

    rect = newRect;

    for(auto& line:lines)
        line->Update(dt);

    cursor->Update(dt);
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

    cursor->RenderDebug();

}

void TextArea::InsertLineAtEnd()
{

    if(lines.size() == 0)
    {
        lines.push_back(std::make_unique<Line>((*this),renderer,0));
    }
    else
    {
        lines.push_back(std::make_unique<Line>((*this),renderer,lines.size()));
    }
}




void TextArea::GetTextStartCoord(float* x,float* y) const
{
    *x = rect.x + boundaryMarginX;
    *y = rect.y + boundaryMarginY;
}


const Line* TextArea::GetLine(size_t index) const
{
    if(index >= lines.size())
        return nullptr;

    return lines[index].get();
}


//Line

Line::Line(const TextArea& textArea,SDL_Renderer* renderer,int lineNo)
    :textArea(textArea),renderer(renderer),lineNo(lineNo)
{

    float x,y;
    textArea.GetTextStartCoord(&x,&y);

    rect = {x,y,
        textArea.GetRect().w,
        static_cast<float>(textArea.GetFontHeight())
    };

    cursorPosXHistory.push_back(rect.x + linePadx);
}



void Line::RenderDebug()
{
    Uint8 r,g,b,a;

    SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderRect(renderer,&rect);
    SDL_SetRenderDrawColor(renderer,r,g,b,a);
}


void Line::Update(float dt)
{

    float x,y;
    textArea.GetTextStartCoord(&x,&y);

    rect = {x,y,
        textArea.GetRect().w,
        static_cast<float>(textArea.GetFontHeight())
    };

    // need to refresh cursor posX  .

}

void Line::GetLineEndCoordinates(float* x,float* y)const
{
    *x = cursorPosXHistory.back();
    *y = rect.y;
}

//Cursor

Cursor::Cursor(SDL_Renderer* renderer,const TextArea& textArea)
                :renderer(renderer),textArea(textArea)
{
    const Line* line = textArea.GetLine(lineNo);
    if(line == nullptr)
    {
        rect = {
            0,0,
            cursorWidth,
            static_cast<float>(textArea.GetFontHeight())
        };
    }
    {
        float x,y;
        line->GetLineEndCoordinates(&x,&y);

        rect = {
            x,y,
            cursorWidth,
            static_cast<float>(textArea.GetFontHeight() * cursorHeightFactor)
        };
    }
}

void Cursor::RenderDebug()
{
    Uint8 r,g,b,a;
    SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
    SDL_SetRenderDrawColor(
        renderer,
        cursorColor.r,
        cursorColor.g,
        cursorColor.b,
        cursorAlpha
    );

    SDL_RenderRect(renderer,&rect);
    SDL_SetRenderDrawColor(renderer,r,g,b,a);
}

void Cursor::Update(float dt)
{
    animTime += dt;
    if(animTime >= blinkTime)
    {
        if(cursorAlpha == 0)
            cursorAlpha = 255;
        else
            cursorAlpha = 0;

        animTime = 0.0f;
    }
}


