#pragma once
#include <imgui/imgui.h>

#include "../core/Core.h"
#include "GLFW/glfw3.h"

namespace TESLA
{
    class TS_DLL Application
    {
    public:
        //GLFW stuff
        static void Start(const int& windowWidth,const int& windowHeight, const char* name);
        static void Terminate();
        static void PollEvents();
        static void SwapBuffers();
        static void SetMouseButtonCallback(GLFWmousebuttonfun callback);
        static void SetMouseCursorCallback(GLFWcursorposfun callback);
        static void SetInputMode(int mode, int value);
        static int GetKey(int key);
        static bool WindowShouldClose();
        static double GetTime();

        //ImGUI stuff
        static void InitImGUI();
        static void CreateImGUINewFrame();
        static void SetImGUIFocus(const char* windowName);
        static void ImGUIRender();
        static bool ImGUIWantsMouse();
        static bool ImGUIWantsKeyboard();
        static void ReturnMouse();
        static void ReturnCursor();

        //ImGUI GUI creation
        static void BeginGUI(const char* name, bool* _openWidget = nullptr, const ImGuiWindowFlags& flags = 0);
        static void EndGUI();
        static bool CreateButton(const char* name);
        static bool CreateInputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = 0, void* user_data = 0);
    };
}
