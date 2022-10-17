#pragma once
#include "../../core/Core.h"
#include "Layer.h"

namespace TESLA
{
    class TS_DLL LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(TESLA::Layer* layer);
        void PushOverlay(TESLA::Layer* overlay);

        void PopLayer(TESLA::Layer* layer);
        void PopOverlay(TESLA::Layer* overlay);

        std::vector<TESLA::Layer*>::iterator begin(){return m_Layers.begin();}
        std::vector<TESLA::Layer*>::iterator end(){return m_Layers.end();}
    private:
        std::vector<TESLA::Layer*> m_Layers;
        std::vector<TESLA::Layer*>::iterator m_LayerInsert;
    };
}
