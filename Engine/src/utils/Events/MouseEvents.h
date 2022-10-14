#pragma once
#include "Event.h"

namespace TESLA
{
    class TS_DLL MouseEvent : public Event
    {
    public:
        MouseEvent() = delete;
        EventCategory GetCategory() override
        {
            return TESLA::EventCategory::Mouse;
        }
    };

    class TS_DLL MouseMovedEvent : public MouseEvent
    {
    public:
        MouseMovedEvent(const float& mouseX, const float& mouseY)
            :MouseEvent(), m_mouseX(mouseX), m_mouseY(mouseY){}
        EventType GetType() override
        {
            return TESLA::EventType::MouseMoved;
        }
        float GetMouseX()
        {
            return m_mouseX;
        }
        float GetMouseY()
        {
            return m_mouseY;
        }
    private:
        float m_mouseX, m_mouseY;
    };

    class TS_DLL MouseScrolledEvent : public MouseEvent
    {
    public:
        MouseScrolledEvent(float scrollDelta)
            :MouseEvent(), m_scrollDelta(scrollDelta){}
        EventType GetType() override
        {
            return TESLA::EventType::MouseScrolled;
        }
        float GetScrollDelta()
        {
            return m_scrollDelta;
        }
    
    private:
        float m_scrollDelta;
    };
}
