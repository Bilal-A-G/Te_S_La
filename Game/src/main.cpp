#include "Te_S_La.h"
#include "GLFW/glfw3.h"

GLFWwindow* window;
int window_height = 800;
int window_width = 1200;

#define GLOBAL_UP_VECTOR glm::vec3(0, 1, 0)

float nearPlane = 0.1f;
float farPlane = 200.0f;

float angle = 0.0f;
TESLA::Model* gun;
TESLA::Model* suzanne;

void LogGLFWErrors(int id, const char* error_message) {TS_LOG_MESSAGE(spdlog::level::err, "GLFW error: {0}, ID = {1}", error_message, id);}
void ResizeWindow(GLFWwindow* _, int width, int height) {TESLA::GLADWrapper::UpdateViewport(width, height);}

TESLA::Model* CreateMesh(const char* fileName)
{
    const glm::mat4 projection = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width)/static_cast<float>(window_height), nearPlane, farPlane);
    const glm::mat4 view = glm::lookAt( glm::vec3(1.5f, 1.0f, 1.5f), glm::vec3(0.0f),GLOBAL_UP_VECTOR);
    
    TESLA::Shader basicShader;
    const GLuint shaderProgram = basicShader.GetProgram();

    return new TESLA::Model(fileName, shaderProgram, view, projection);
}

void Init()
{
    glfwSetErrorCallback(LogGLFWErrors);
    if(glfwInit())
        TS_LOG_MESSAGE(spdlog::level::info, "GLFW successfully intialized");
    else
        TS_LOG_MESSAGE(spdlog::level::err, "GLFW failed to initialize"); 
    
    window = glfwCreateWindow(window_width, window_height, "Game", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if(window == nullptr)
        TS_LOG_MESSAGE(spdlog::level::err, "Failed to create a window");
    else
        TS_LOG_MESSAGE(spdlog::level::info, "Successfully created a window");


    //Checking if GLAD is working or not
    if(TESLA::GLADWrapper::LoadGLAD(glfwGetProcAddress) == false)
        TS_LOG_MESSAGE(spdlog::level::err, "Failed to initialize GLAD");
    else
        TS_LOG_MESSAGE(spdlog::level::info, "Successfully initialized GLAD");


    TESLA::GLADWrapper::UpdateViewport(window_width, window_height);
    glfwSetFramebufferSizeCallback(window, ResizeWindow);

    suzanne = CreateMesh("Suzanne.obj");
    suzanne->Scale(glm::vec3(0.5, 0.5, 0.5));
    suzanne->Translate(glm::vec3(-1, 0, 0));

    gun = CreateMesh("BG60.obj");
    gun->Scale(glm::vec3(0.3,0.3,0.3));
    gun->Translate(glm::vec3(1, 0, 0));
}

void Render()
{
    glfwSwapBuffers(window);
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window))
    {
        TESLA::ExitApplication();
    }

    TESLA::GLADWrapper::OpenGLRender();
    
    angle += 1;
    if(angle > 360) angle = 0.0f;
    
    gun->Draw();
    gun->Rotate(angle, GLOBAL_UP_VECTOR);

    suzanne->Draw();

    glfwPollEvents();
}

void CleanUp()
{
    delete gun;
    gun = nullptr;

    delete suzanne;
    suzanne = nullptr;
    
    glfwTerminate();
}
