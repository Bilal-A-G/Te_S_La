#pragma once
#include <vector>

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
        void Handle()
        {
            handled = true;
            //Temporary, will probs not be deleting the event after handling in the future
            delete this;
        }
        bool handled = false;
    };
    
    class TS_DLL EventListener
    {
    public:
        EventListener() = delete;
        static void Invoke(Event* event);
        static void Subscribe(void (*EventFunc)(TESLA::Event*), const TESLA::EventCategory& type);
    private:
        static std::vector<void(*)(TESLA::Event*)> subscribers;
        static std::vector<TESLA::EventCategory> listenerTypes;
    };
}
