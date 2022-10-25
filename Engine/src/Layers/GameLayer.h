#pragma once
#include "../EventSystem/Layers/Layer.h"

namespace TESLA
{
    class GameLayer : public Layer
    {
    public:
        void DispatchEvent(TESLA::EventFunction function, TESLA::Event* event) override;
    };
}
