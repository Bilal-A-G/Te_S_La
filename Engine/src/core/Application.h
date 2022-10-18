#pragma once
#include <imgui/imgui.h>

#include "Window.h"
#include "../core/Core.h"
#include "../utils/events/LayerStack.h"

namespace TESLA
{
    class TS_DLL Application
    {
    public:
        //App stuff
        static void Start(const int& windowWidth,const int& windowHeight, const char* name);
        static void Update();
        static void LateUpdate();
        static void WindowUpdate();
        static void Terminate();
        
        //GLFW stuff
        static void SetInputMode(int mode, int value);
        static double GetTime();

        //ImGUI GUI creation
        static void BeginGUI(const char* name, bool* _openWidget = nullptr, const ImGuiWindowFlags& flags = 0);
        static void EndGUI();
        static bool CreateButton(const char* name);
        static bool CreateInputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = 0, void* user_data = 0);

        static void PushLayer(Layer* layer);
        static void PushOverlay(Layer* overlay);
        static void DispatchEvent(TESLA::EventFunction function, TESLA::Event* event);
        static TESLA::Window* GetWindow()
        {
            return m_window;
        }
    private:
        static LayerStack m_layerStack;
        static TESLA::Window* m_window;
    };
}
