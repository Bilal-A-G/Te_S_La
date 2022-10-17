#pragma once
#include "../utils/events/Layer.h"

class TestLayer : public TESLA::Layer
{
public:
    void DispatchEvent(TESLA::EventFunction function, TESLA::Event* event) override
    {
        function(event);
        event->Handle();
    }
};
