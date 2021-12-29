#pragma once

#include "Sofia/Geometry/Rectangle.h"
#include "Sofia/Graphics/GraphicsContext.h"
#include "Sofia/Graphics/Color.h"
#include "Sofia/Input.h"

#include <string>
#include <functional>

namespace sf::widgets
{
    bool Button(const std::string& text, const Rectangle& rect = Rectangle());
    void Cursor();

    unsigned int GenerateId(const std::string& key);
}

