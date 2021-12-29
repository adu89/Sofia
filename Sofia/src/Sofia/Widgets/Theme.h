#pragma once

#include "Sofia/Graphics/Color.h"

namespace sf
{
    struct Theme
    {
        Theme();
        Theme(const Theme&) = delete;
        Theme(Theme&&) = delete;
        Theme& operator=(Theme&&) = delete;
        Theme& operator=(const Theme&) = delete;

        Color ButtonBackgroundColor = Colors::Black;
        Color ButtonHoverColor = Colors::Blue;
        Color ButtonTextColor = Colors::White;
        Color TextColor = Colors::White;

        static Theme& Instance();
    };
}