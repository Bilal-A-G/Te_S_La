#pragma once
#include "../core/core.h"
#include "../utils/events/Layer.h"

namespace TESLA
{
    class TS_DLL GuiLayer : public TESLA::Layer
    {
    public:
        void OnUpdate() override;
        void OnLateUpdate() override;
    
        void OnAttach() override;
        void OnDetach() override;
        void DispatchEvent(TESLA::EventFunction function, TESLA::Event* event) override;
    };

}
