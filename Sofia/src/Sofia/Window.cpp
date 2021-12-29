#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace sf
{
    Window* Window::Create(const WindowProperties& WindowProperties)
    {
        return new WindowsWindow(WindowProperties);
    }
}