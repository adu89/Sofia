#pragma once

#include "Sofia/Input.h"

namespace sf
{
    class WindowsInput : public Input
    {
    public:
        WindowsInput();
        MousePosition GetMousePosition() override;
        bool IsMouseButtonPressed(MouseButton mouseButton) override;
    }; 
} 
