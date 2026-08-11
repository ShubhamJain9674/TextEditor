#pragma once
#include "Command.hpp"
#include <SDL3/SDL_rect.h>


class IFocusable : public ICommandHandler
{
public:
    explicit IFocusable(SDL_FRect& rect)
        :rect(rect)
    {

    }
    virtual ~IFocusable() = default;

    bool IsUnderMouse(float mouseX,float mouseY)const
    {
        SDL_FPoint point { mouseX, mouseY };
        return SDL_PointInRectFloat(&point, &rect);
    }


private:
    const SDL_FRect& rect;
};



