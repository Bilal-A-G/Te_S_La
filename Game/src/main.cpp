#include "Te_S_La.h"
#include "GLFW/glfw3.h"

GLFWwindow* window;
int window_height = 800;
int window_width = 1200;

#define GLOBAL_UP_VECTOR glm::vec3(0, 1, 0)

float nearPlane = 0.1f;
float farPlane = 200.0f;

float angle = 0.0f;
TESLA::Model* suzanne2;
TESLA::Model* suzanne1;

glm::mat4 projection = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width)/static_cast<float>(window_height), nearPlane, farPlane);
glm::mat4 view = glm::lookAt( glm::vec3(1.5f, 1.0f, 1.5f), glm::vec3(0.0f),GLOBAL_UP_VECTOR);

void LogGLFWErrors(int id, const char* error_message) {TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "GLFW error: {0}, ID = {1}", error_message, id);}
void ResizeWindow(GLFWwindow* _, int width, int height) {TESLA::GLADWrapper::UpdateViewport(width, height);}

TESLA::Model* CreateMesh(const char* fileName, const char* modelName)
{
    TESLA::Shader basicShader;
    const GLuint shaderProgram = basicShader.GetProgram();

    return new TESLA::Model(fileName, modelName, shaderProgram, view, projection);
}

void Init()
{
    glfwSetErrorCallback(LogGLFWErrors);
    if(glfwInit())
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "GLFW successfully intialized");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "GLFW failed to initialize"); 
    
    window = glfwCreateWindow(window_width, window_height, "Game", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if(window == nullptr)
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to create a window");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully created a window");


    //Checking if GLAD is working or not
    if(TESLA::GLADWrapper::LoadGLAD(glfwGetProcAddress) == false)
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to initialize GLAD");
    else
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully initialized GLAD");


    TESLA::GLADWrapper::UpdateViewport(window_width, window_height);
    glfwSetFramebufferSizeCallback(window, ResizeWindow);

    suzanne1 = CreateMesh("Suzanne.obj", "Monkey1");
    suzanne1->Scale(glm::vec3(0.5, 0.5, 0.5));
    suzanne1->Translate(glm::vec3(-1, 0, 0));

    suzanne2 = CreateMesh("Suzanne.obj", "Monkey2");
    suzanne2->Scale(glm::vec3(0.3,0.3,0.3));
    suzanne2->Translate(glm::vec3(1, 0, 0));
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
    
    suzanne2->Draw();
    suzanne2->Rotate(angle, GLOBAL_UP_VECTOR);

    suzanne1->Draw();
    suzanne1->Rotate(angle, GLOBAL_UP_VECTOR);

    glfwPollEvents();
}

void CleanUp()
{
    delete suzanne1;
    suzanne1 = nullptr;

    delete suzanne2;
    suzanne2 = nullptr;
    
    glfwTerminate();
}
