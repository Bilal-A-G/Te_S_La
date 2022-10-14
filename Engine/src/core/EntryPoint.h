#pragma once
#include "../utils/Logger.h"
#include "Application.h"
#include "utils/GLADWrapper.h"

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
    TESLA::Application::InitImGUI();
    
    while (runApplication)
    {
        if(TESLA::Application::WindowShouldClose())
            TESLA::ExitApplication();
        
        TESLA::Application::SwapBuffers();
        TESLA::GLADWrapper::OpenGLRender();
        TESLA::Application::CreateImGUINewFrame();
        Render();
        DrawGUIs();
        TESLA::Application::ImGUIRender();
        TESLA::Application::PollEvents();
    }

    CleanUp();
    TESLA::Application::Terminate();
}
