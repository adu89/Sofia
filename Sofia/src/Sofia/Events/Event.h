#pragma once

#include <functional>
#include <sstream>

namespace sf
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MousButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    class Event
    {
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool Handled = false;
    };

    class EventDispatcher
    {
        template<class T>
        using EventFunction = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& event)
            : event(event)
        {
        }

        template<class T>
        bool Dispatch(EventFunction<T> function)
        {
            if(event.GetEventType() == T::GetStaticType())
            {
                event.Handled = function(*(T*)&event);
                return true;
            }

            return false;
        }
    
    private:
        Event& event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}