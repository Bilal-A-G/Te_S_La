#include "TSpch.h"
#include "GuiLayer.h"
#include "../core/Application.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

void TESLA::GuiLayer::OnAttach()
{
    TESLA::Application::GetWindow()->InitImGUI();
}

void TESLA::GuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void TESLA::GuiLayer::OnUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void TESLA::GuiLayer::OnLateUpdate()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void TESLA::GuiLayer::DispatchEvent(TESLA::EventFunction function, TESLA::Event* event)
{
    if(ImGui::GetIO().WantCaptureMouse && event->GetCategory() == TESLA::EventCategory::Mouse)
    {
        event->Handle();
    }
    else if(ImGui::GetIO().WantCaptureKeyboard && event->GetCategory() == TESLA::EventCategory::Keyboard)
    {
        event->Handle();
    }
}




