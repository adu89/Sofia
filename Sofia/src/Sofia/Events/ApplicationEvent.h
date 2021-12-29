#pragma once

#include "Sofia/Events/Event.h"

namespace sf
{
    class WindowCloseEvent : public Event
    {
    public:
        EventType GetEventType() const override { return EventType::WindowClose; }
        const char* GetName() const override { return "WindowClose"; }
        static EventType GetStaticType() { return EventType::WindowClose; }     
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int heigh)
            : width(width), height(height)
        {
        }

        int GetWidth() { return width; }
        int GetHeight() { return height; }

        EventType GetEventType() const override { return EventType::WindowResize; }
        const char* GetName() const override { return "WindowResize"; }
        static EventType GetStaticType() { return EventType::WindowResize; }     

        private:
            int width;
            int height;
    };

    class AppUpdateEvent : public Event
    {
    public:
        EventType GetEventType() const override { return EventType::AppUpdate; }
        const char* GetName() const override { return "AppUpdate"; }
        static EventType GetStaticType() { return EventType::AppUpdate; }           
    };
}