#pragma once
#include "Event.h"

namespace TESLA
{
    class KeyEvent : public Event
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

    class KeyboardButtonEvent : public KeyEvent
    {
    public:
        KeyboardButtonEvent(const int& keycode, const bool& pressed)
            :KeyEvent(keycode, pressed){}
        
        EventCategory GetCategory() override
        {
            return TESLA::EventCategory::Keyboard;
        }
    };

    class MouseButtonEvent : public KeyEvent
    {
    public:
        MouseButtonEvent(const int& keycode, const bool& pressed)
            :KeyEvent(keycode, pressed){}

        EventCategory GetCategory() override
        {
            return TESLA::EventCategory::Mouse;
        }
    };
}
