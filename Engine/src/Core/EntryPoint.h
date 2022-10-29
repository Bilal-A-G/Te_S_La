#pragma once
#include "TSpch.h"
#include "Application.h"
#include "input/Input.h"
#include "Rendering/RenderCommand.h"

inline bool runApplication = true;

namespace TESLA
{
    inline void ExitApplication()
    {
        runApplication = false;
    }
}

extern void Init();
extern void Render();
extern void CleanUp();
extern void DrawGUIs();

int main(int argc, char* argv[])
{
    TESLA::Logger::Init();
    Init();
    TESLA::Input::Init();
    TESLA::EventListener::Subscribe({[](TESLA::Event* event){TESLA::ExitApplication();}, TESLA::EventType::WindowClosed, TESLA::EventCategory::Application});
    
    while (runApplication)
    {
        TESLA::Application::WindowUpdate();
        TESLA::RenderCommand::SetClearColour({0.1f, 0.1f, 0.1f, 0.0f});
        TESLA::RenderCommand::Clear();
        TESLA::Application::Update();
        TESLA::Input::Update();
        TESLA::Renderer::BeginScene();
        Render();
        TESLA::Renderer::EndScene();
        DrawGUIs();
        TESLA::Application::LateUpdate();
    }

    CleanUp();
    TESLA::Application::Terminate();
}
