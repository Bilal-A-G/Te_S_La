﻿#pragma once
#include "Event.h"

namespace TESLA
{
    class TS_DLL KeyEvent : public Event
    {
    public:
        int GetKeycode()
        {
            return m_keycode;
        }
        EventType GetType() override
        {
            return m_pressed ? TESLA::EventType::ButtonPressed : TESLA::EventType::ButtonReleased;
        }
    protected:
        KeyEvent(const int& keycode, const bool& pressed) 
            : m_keycode(keycode), m_pressed(pressed){}
        int m_keycode;
        bool m_pressed;
    };

    class TS_DLL KeyboardButtonEvent : public KeyEvent
    {
    public:
        KeyboardButtonEvent(const int& keycode, const bool& pressed)
            : KeyEvent(keycode, pressed){}
        EventCategory GetCategory() override
        {
            return TESLA::EventCategory::Keyboard;
        }
    };

    class TS_DLL MouseButtonEvent : public KeyEvent
    {
    public:
        MouseButtonEvent(const int& keycode, const bool& pressed)
            : KeyEvent(keycode, pressed){}
        EventCategory GetCategory() override
        {
            return TESLA::EventCategory::Mouse;
        }
    };
}
