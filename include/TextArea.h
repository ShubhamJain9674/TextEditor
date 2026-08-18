#pragma once
#include "GapBuffer.h"
#include "Focusable.hpp"



class TextArea : public IFocusable
{
public:
    TextArea() = default;
    ~TextArea() = default;


    // void OnFocused()override;
    // void OnUnfocused()override;

    std::string GetName()override { return "TextArea"; }


};

