#pragma once
#include "Event.h"
#include "MouseEvents.h"

namespace TESLA
{
    class TS_DLL KeyEvent : public Event
    {
    public:
        KeyEvent(const int& keycode, const bool& pressed) 
            : m_keycode(keycode), m_pressed(pressed){}
        int GetKeycode()
        {
            return m_keycode;
        }

        EventType GetType() override
        {
            return m_pressed ? TESLA::EventType::ButtonPressed : TESLA::EventType::ButtonReleased;
        }
    protected:
        int m_keycode;
        bool m_pressed;
    };

    class TS_DLL KeyboardButtonEvent : public KeyEvent
    {
    public:
        using KeyEvent::KeyEvent;
        
        EventCategory GetCategory() override
        {
            return TESLA::EventCategory::Keyboard;
        }
    };

    class TS_DLL MouseButtonEvent : public KeyEvent, public MouseEvent
    {
    public:
        using KeyEvent::KeyEvent;
    };
}
