﻿#pragma once
#include "Window.h"
#include "../EventSystem/Layers/LayerStack.h"
#include "../Rendering/Buffer.h"

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
        static TESLA::VertexBuffer* GetVBO(){return m_vbo;}
        static TESLA::ElementBuffer* GetEBO(){return m_ebo;}
        
    private:
        static LayerStack m_layerStack;
        static TESLA::Window* m_window;
        static TESLA::VertexBuffer* m_vbo;
        static TESLA::ElementBuffer* m_ebo;
    };
}