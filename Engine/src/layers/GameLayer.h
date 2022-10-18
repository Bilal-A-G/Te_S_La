#pragma once
#include "../core/Core.h"
#include "../utils/events/Layer.h"

namespace TESLA
{
    class TS_DLL GameLayer : public Layer
    {
    public:
        void DispatchEvent(TESLA::EventFunction function, TESLA::Event* event) override;
    };
}
