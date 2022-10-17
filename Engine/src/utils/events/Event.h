#pragma once
#include "../../TSpch.h"
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
    };

    struct Subscriber
    {
        Subscriber(void(*EventFunc)(TESLA::Event*), const TESLA::EventType type, const TESLA::EventCategory category)
            :EventFunc(EventFunc), type(type), category(category){}
        
        void(*EventFunc)(TESLA::Event*);
        TESLA::EventType type;
        TESLA::EventCategory category;
    };
    
    class TS_DLL EventListener
    {
    public:
        EventListener() = delete;
        static void Invoke(Event* event);
        static void Subscribe(const Subscriber& subscriber);
        static void UnSubscribe(void(*EventFunc)(TESLA::Event*));
    private:
        static std::vector<Subscriber> m_subscribers;
    };
}
