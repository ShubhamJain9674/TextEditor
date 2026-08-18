#pragma once
#include "Command.hpp"
#include <SDL3/SDL_rect.h>


class IFocusable : public ICommandHandler
{
public:
    IFocusable() = default;

    virtual ~IFocusable() = default;

    bool IsUnderMouse(float mouseX,float mouseY)const
    {
        SDL_FPoint point { mouseX, mouseY };
        return SDL_PointInRectFloat(&point, &rect);
    }


    virtual void OnFocused(){};

    virtual void OnUnfocused(){};

    virtual std::string GetName() = 0;


protected:
    SDL_FRect rect{};
};



