#include "TSpch.h"
#include "Application.h"
#include "Window.h"

#include "../layers//GuiLayer.h"
#include "../layers/GameLayer.h"

TESLA::Window* TESLA::Application::m_window;
TESLA::LayerStack TESLA::Application::m_layerStack;

void TESLA::Application::Start(const int& windowWidth,const int& windowHeight, const char* name)
{
    m_window = TESLA::Window::Create({windowWidth, windowHeight, name});
    PushLayer(new GuiLayer());
    PushLayer(new GameLayer());
}

void TESLA::Application::PushLayer(Layer* layer)
{
    m_layerStack.PushLayer(layer);
    layer->OnAttach();
}

void TESLA::Application::PushOverlay(Layer* overlay)
{
    m_layerStack.PushOverlay(overlay);
    overlay->OnAttach();
}

void TESLA::Application::DispatchEvent(TESLA::EventFunction function, TESLA::Event* event)
{
    for(auto layer = m_layerStack.end(); layer != m_layerStack.begin();)
    {
        (*--layer)->DispatchEvent(function, event);
        if(event->GetHandled())
            break;
    }
}

void TESLA::Application::Update()
{
    for(Layer* layer : m_layerStack)
        layer->OnUpdate();
}

void TESLA::Application::WindowUpdate()
{
    m_window->Update();
}

void TESLA::Application::LateUpdate()
{
    for(Layer* layer : m_layerStack)
        layer->OnLateUpdate();
}

void TESLA::Application::Terminate()
{
    for(Layer* layer : m_layerStack)
        layer->OnDetach();
    
    glfwTerminate();
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
    m_window->SetInputMode(mode, value);
}




