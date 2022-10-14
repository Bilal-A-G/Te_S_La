#include "Application.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "../utils/Rendering/GLADWrapper.h"
#include "../utils/Logging//Logger.h"

static GLFWwindow* window;

void LogGLFWErrors(int id, const char* error_message) {TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "GLFW error: {0}, ID = {1}", error_message, id);}
void ResizeWindow(GLFWwindow* _, int width, int height) {TESLA::GLADWrapper::UpdateViewport(width, height);}

void TESLA::Application::Start(const int& windowWidth,const int& windowHeight, const char* name)
{
    TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Application started");
    if(glfwInit())
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully initialized GLFW");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to initialize GLFW");

    glfwSetErrorCallback(LogGLFWErrors);
    window = glfwCreateWindow(windowWidth, windowHeight, name, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if(window != nullptr)
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully created a window");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to create a window");

    if(TESLA::GLADWrapper::LoadGLAD(glfwGetProcAddress))
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully initialized GLAD");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to initialize GLAD");

    TESLA::GLADWrapper::UpdateViewport(windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, ResizeWindow);
}

void TESLA::Application::PollEvents()
{
    glfwPollEvents();
}

void TESLA::Application::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void TESLA::Application::InitImGUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void TESLA::Application::SetMouseButtonCallback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(window, callback);
}

void TESLA::Application::SetMouseCursorCallback(GLFWcursorposfun callback)
{
    glfwSetCursorPosCallback(window, callback);
}


int TESLA::Application::GetKey(int key)
{
    return glfwGetKey(window, key);
}

bool TESLA::Application::WindowShouldClose()
{
    return glfwWindowShouldClose(window);
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
    SetMouseButtonCallback(ImGui_ImplGlfw_MouseButtonCallback);
}

void TESLA::Application::ReturnCursor()
{
    SetMouseCursorCallback(ImGui_ImplGlfw_CursorPosCallback);
}


void TESLA::Application::SetImGUIFocus(const char* windowName)
{
    ImGui::SetWindowFocus(windowName);
}

void TESLA::Application::SetInputMode(int mode, int value)
{
    glfwSetInputMode(window, mode, value);
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