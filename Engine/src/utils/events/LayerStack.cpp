#include "TSpch.h"
#include "LayerStack.h"

TESLA::LayerStack::LayerStack()
{
    m_LayerInsert = m_Layers.begin();
}

TESLA::LayerStack::~LayerStack()
{
    m_Layers.clear();
}

void TESLA::LayerStack::PopLayer(TESLA::Layer* layer)
{
    auto foundLayer = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if(foundLayer != m_Layers.end())
    {
        m_Layers.erase(foundLayer);
        --m_LayerInsert;
    }
}

void TESLA::LayerStack::PopOverlay(TESLA::Layer* overlay)
{
    auto foundOverlay = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if(foundOverlay != m_Layers.end())
    {
        m_Layers.erase(foundOverlay);
    }
}

void TESLA::LayerStack::PushLayer(TESLA::Layer* layer)
{
    m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
}

void TESLA::LayerStack::PushOverlay(TESLA::Layer* overlay)
{
    m_Layers.emplace_back(overlay);
}





