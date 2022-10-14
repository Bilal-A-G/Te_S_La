#pragma once
#include "../../core/Core.h"

namespace TESLA
{
    enum EventCategory
    {
        Mouse,
        Keyboard,
        Application
    };

    enum EventType
    {
        ButtonPressed,
        ButtonReleased,
        MouseScrolled,
        MouseMoved,

        WindowClosed,
        WindowResized,
        WindowFocused,
        WindowLostFocus,
        WindowMoved
    };

    class TS_DLL Event
    {
    public:
        virtual EventCategory GetCategory() = 0;
        virtual EventType GetType() = 0;
        bool GetHandled()
        {
            return handled;
        }
    protected:
        virtual ~Event() = default;
        Event();
        bool handled = false;
    };
}
