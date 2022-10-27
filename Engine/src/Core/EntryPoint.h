#pragma once
#include "TSpch.h"
#include "Application.h"
#include "input/Input.h"

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
        TESLA::Application::GetRenderer()->Clear();
        TESLA::Application::Update();
        TESLA::Input::Update();
        TESLA::Application::GetRenderer()->BeginScene();
        Render();
        TESLA::Application::GetRenderer()->EndScene();
        DrawGUIs();
        TESLA::Application::LateUpdate();
    }

    CleanUp();
    TESLA::Application::Terminate();
}
