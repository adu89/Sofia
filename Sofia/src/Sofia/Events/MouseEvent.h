#pragma once

#include "Sofia/Events/Event.h"

namespace sf
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(int x, int y)
            : x(x), y(y)
        {
        }

        int GetX() { return x; }
        int GetY() { return y; }

        EventType GetEventType() const override { return EventType::MouseMoved; }
        const char* GetName() const override { return "MouseMoved"; }
        static EventType GetStaticType() { return EventType::MouseMoved; }     

        private:
            int x;
            int y;
    };
}