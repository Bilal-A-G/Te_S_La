#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Te_S_La.h"
#include "CameraMovement.h"


GLFWwindow* window;
int window_height = 800;
int window_width = 1200;

float nearPlane = 0.1f;
float farPlane = 200.0f;

#define GLOBAL_UP_VECTOR glm::vec3(0, 1, 0)

glm::mat4 projection = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width)/static_cast<float>(window_height), nearPlane, farPlane);
glm::mat4 view = glm::mat4(0);

void LogGLFWErrors(int id, const char* error_message) {TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "GLFW error: {0}, ID = {1}", error_message, id);}
void ResizeWindow(GLFWwindow* _, int width, int height) {TESLA::GLADWrapper::UpdateViewport(width, height);}

TESLA::Model* ImportModel(const char* fileName)
{
    TESLA::Shader basicShader;
    GLuint shaderProgram = basicShader.GetProgram();

    return new TESLA::Model{fileName, shaderProgram, view, projection};
}

std::vector<TESLA::Model*> sceneObjects;

void Init()
{
    TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Application started");
    if(glfwInit())
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully initialized GLFW");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to initialize GLFW");

    glfwSetErrorCallback(LogGLFWErrors);
    window = glfwCreateWindow(window_width, window_height, "Editor", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if(window != nullptr)
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully created a window");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to create a window");

    if(TESLA::GLADWrapper::LoadGLAD(glfwGetProcAddress))
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully initialized GLAD");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to initialize GLAD");

    TESLA::GLADWrapper::UpdateViewport(window_width, window_height);
    glfwSetFramebufferSizeCallback(window, ResizeWindow);

    sceneObjects.push_back(ImportModel("cube.obj"));
    sceneObjects[0]->Translate(glm::vec3(0, -1, 0));

    sceneObjects.push_back(ImportModel("cube.obj"));
    sceneObjects[1] ->Translate(glm::vec3(1, 1, 1));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Render()
{
    glfwSwapBuffers(window);
    TESLA::GLADWrapper::OpenGLRender();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if(!ImGui::GetIO().WantCaptureMouse)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window))
            TESLA::ExitApplication();
        view = CameraMovement::Look(window);
    }
    else
    {
        glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
    }
    
    for (TESLA::Model* model : sceneObjects)
    {
        model->Draw();
    }

    ImGui::Begin("Create");
    if(ImGui::Button("Create Object"))
    {
        ImGui::Text("You created a new cube");
    }
    ImGui::End();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    glfwPollEvents();
}

void CleanUp()
{
    TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Application ended");

    for(TESLA::Model* model : sceneObjects)
        delete model;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    sceneObjects.clear();
    
    glfwTerminate();
}