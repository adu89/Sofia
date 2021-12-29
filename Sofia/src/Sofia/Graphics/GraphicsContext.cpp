#include "GraphicsContext.h"

#include "Platform/Windows/WindowsGraphicsContext.h"

namespace sf
{
    GraphicsContext& GraphicsContext::Instance()
    {
        static WindowsGraphicsContext graphicsContext;
        return graphicsContext;
    }
}