#pragma once
#include "TSpch.h"
#include "Application.h"
#include "utils/rendering/GLADWrapper.h"

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
    TESLA::EventListener::Subscribe({[](TESLA::Event* event){TESLA::ExitApplication();}, TESLA::EventType::WindowClosed, TESLA::EventCategory::Application});
    
    while (runApplication)
    {
        TESLA::Application::WindowUpdate();
        TESLA::GLADWrapper::OpenGLRender();
        TESLA::Application::Update();
        Render();
        DrawGUIs();
        TESLA::Application::LateUpdate();
    }

    CleanUp();
    TESLA::Application::Terminate();
}
