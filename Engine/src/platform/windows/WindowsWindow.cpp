﻿#include "TSpch.h"
#include "WindowsWindow.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "../../utils/rendering/GLADWrapper.h"

void LogGLFWErrors(int id, const char* error_message) {TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "GLFW error: {0}, ID = {1}", error_message, id);}
void ResizeWindow(GLFWwindow* _, int width, int height) {TESLA::GLADWrapper::UpdateViewport(width, height);}

static bool initializedGLFW;

void TESLA::WindowsWindow::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_data->window);
}

TESLA::Window* TESLA::Window::Create(const WindowProperties& properties)
{
    return new WindowsWindow(properties);
}

TESLA::WindowsWindow::WindowsWindow(const WindowProperties& properties)
{
    if(!initializedGLFW)
    {
        const int initialized = glfwInit();
        TS_LOG_ASSERTION(initialized == GLFW_TRUE, TESLA_LOGGER::ERR, "Failed to initialize GLFW");
        glfwSetErrorCallback(LogGLFWErrors);

        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully initialized GLFW");
        initializedGLFW = true;
    }
    
    GLFWwindow* window = glfwCreateWindow(properties.width, properties.height, properties.name.data(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    TS_LOG_ASSERTION((window != nullptr), TESLA_LOGGER::ERR, "Failed to create window");
    TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully created window, width = {0}, height = {1}, name = {2}", properties.width, properties.height, properties.name);

    m_data = new WindowsWindowProperties(properties.width, properties.height, properties.name.data(), true, window);
    
    const bool gladLoaded = TESLA::GLADWrapper::LoadGLAD(glfwGetProcAddress);

    TS_LOG_ASSERTION(gladLoaded, TESLA_LOGGER::ERR, "Failed to load GLAD");
    TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully loaded GLAD");
    
    TESLA::GLADWrapper::UpdateViewport(properties.width, properties.height);
    glfwSetFramebufferSizeCallback(m_data->window, ResizeWindow);

    WindowsWindow::SetVSync(true);
}

void TESLA::WindowsWindow::SetVSync(const bool& set)
{
    glfwSwapInterval(set ? 1 : 0);
    m_data->vSync = set;
}

void TESLA::WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
{
    
}

int TESLA::WindowsWindow::GetKey(const int& key)
{
    return glfwGetKey(m_data->window, key);
}

void TESLA::WindowsWindow::SetInputMode(int mode, int value)
{
    glfwSetInputMode(m_data->window, mode, value);
}

bool TESLA::WindowsWindow::WindowShouldClose()
{
    return glfwWindowShouldClose(m_data->window);
}

void TESLA::WindowsWindow::InitImGUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_data->window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void TESLA::WindowsWindow::SetMouseButtonCallback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(m_data->window, callback);
}

void TESLA::WindowsWindow::SetMouseCursorCallback(GLFWcursorposfun callback)
{
    glfwSetCursorPosCallback(m_data->window, callback);
}












