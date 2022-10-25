#include "TSpch.h"
#include "GameLayer.h"

void TESLA::GameLayer::DispatchEvent(TESLA::EventFunction function, TESLA::Event* event)
{
    function(event);
}

