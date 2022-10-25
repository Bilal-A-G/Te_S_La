#pragma once
#include "../EventSystem/Layers/Layer.h"

namespace TESLA
{
    class GuiLayer : public TESLA::Layer
    {
    public:
        void OnUpdate() override;
        void OnLateUpdate() override;
    
        void OnAttach() override;
        void OnDetach() override;
        void DispatchEvent(TESLA::EventFunction function, TESLA::Event* event) override;
    };

}
