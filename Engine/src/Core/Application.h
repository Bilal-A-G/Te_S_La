#pragma once
#include "Window.h"
#include "../EventSystem/Layers/LayerStack.h"
#include "../Rendering/Renderer.h"

namespace TESLA
{
    class Application
    {
    public:
        static void Start(const int& windowWidth,const int& windowHeight, const char* name);
        static void Update();
        static void LateUpdate();
        static void WindowUpdate();
        static void Terminate();

        static void PushLayer(Layer* layer);
        static void PushOverlay(Layer* overlay);
        static void DispatchEvent(TESLA::EventFunction function, TESLA::Event* event);
        static TESLA::Window* GetWindow(){return m_window;}
        static TESLA::Renderer* GetRenderer(){return m_renderer;}
    private:
        static LayerStack m_layerStack;
        static TESLA::Renderer* m_renderer;
        static TESLA::Window* m_window;
    };
}
