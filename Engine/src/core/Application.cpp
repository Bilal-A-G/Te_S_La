#include "TSpch.h"
#include "Application.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Window.h"

TESLA::Window* window;

void TESLA::Application::Start(const int& windowWidth,const int& windowHeight, const char* name)
{
    window = TESLA::Window::Create({windowWidth, windowHeight, name});
}

void TESLA::Application::Update()
{
    window->Update();
}

void TESLA::Application::CreateImGUINewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void TESLA::Application::Terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void TESLA::Application::ImGUIRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool TESLA::Application::ImGUIWantsMouse()
{
    return ImGui::GetIO().WantCaptureMouse;
}

bool TESLA::Application::ImGUIWantsKeyboard()
{
    return ImGui::GetIO().WantCaptureKeyboard;
}


void TESLA::Application::ReturnMouse()
{
    //SetMouseButtonCallback(ImGui_ImplGlfw_MouseButtonCallback);
}

void TESLA::Application::ReturnCursor()
{
    //SetMouseCursorCallback(ImGui_ImplGlfw_CursorPosCallback);
}


void TESLA::Application::SetImGUIFocus(const char* windowName)
{
    ImGui::SetWindowFocus(windowName);
}

double TESLA::Application::GetTime()
{
    return glfwGetTime();
}

bool TESLA::Application::CreateButton(const char* name)
{
    return ImGui::Button(name);
}

void TESLA::Application::BeginGUI(const char* name, bool* openWidget, const ImGuiWindowFlags& flags)
{
    ImGui::Begin(name, openWidget, flags);
}

bool TESLA::Application::CreateInputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    return ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
}


void TESLA::Application::EndGUI()
{
    ImGui::End();
}

void TESLA::Application::SetInputMode(int mode, int value)
{
    window->SetInputMode(mode, value);
}

void TESLA::Application::InitImGUI()
{
    window->InitImGUI();
}




