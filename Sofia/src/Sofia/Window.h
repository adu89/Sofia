#pragma once

#include "Sofia/Geometry/Rectangle.h"
#include "Sofia/Events/Event.h"

#include <string>
#include <functional>
#include <thread>
#include <mutex>

namespace sf
{
    struct WindowProperties
    {
        WindowProperties(const std::string title = "Application Window",
            unsigned int width = 1280,
            unsigned int height = 720)
            : Title(title)
            , Width(width)
            , Height(height)
        {
        }

        std::string Title;
        unsigned int Width;
        unsigned int Height;
    };

    class Window
    {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        virtual ~Window() = default;
        
        virtual void PollEvents() = 0;
        virtual Rectangle GetClientRectangle() = 0;
        virtual void* GetNativeWindow() = 0;
        virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
        
        static Window* Create(const WindowProperties& windowProperties = WindowProperties());
    };
}
