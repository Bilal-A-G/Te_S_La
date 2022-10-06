#include "Shader.h"
#include "Mesh.h"
#include"GLFW/glfw3.h"

#include<iostream>

//This file is the entry point of the entire application, TODO: move entry point somewhere else

#define GLOBAL_UP_VECTOR glm::vec3(0, 1, 0)

float nearPlane = 0.1f;
float farPlane = 200.0f;

int window_height = 800;
int window_width = 1200;

constexpr float mesh_width = 1.0f;
constexpr float mesh_height = 1.0f;
constexpr float mesh_length = 1.0f;

constexpr bool resize_buffer = true;

//TODO: use precompiled headers so you aren't compiling the same headers over and over again
//Various callbacks for glfw

void ResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
    window_height = height;
    window_width = width;
}

void LogGLFWErrors(int id, const char* error_message)
{
#ifdef PS_DEBUG
    std::cout << error_message << " ID = " << id << "\n";
#endif
}

//Checks for key presses and does stuff with them
void ProcessInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

Mesh CreateMesh()
{
    const glm::mat4 projection = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width)/static_cast<float>(window_height), nearPlane, farPlane);
    const glm::mat4 view = glm::lookAt( glm::vec3(1.5f, 1.0f, 1.5f), glm::vec3(0.0f),GLOBAL_UP_VECTOR);
    
    const std::vector<float> vertices
    {
        -mesh_width/2, mesh_height/2, mesh_length/2, 1.0f, 0.0f, 0.0f,
        mesh_width/2, mesh_height/2, mesh_length/2, 0.0f, 1.0f, 0.0f,
        -mesh_width/2, -mesh_height/2, mesh_length/2, 0.0f, 1.0f, 0.0f,
        mesh_width/2, -mesh_height/2, mesh_length/2, 0.0f, 0.0f, 1.0f,

        -mesh_width/2, mesh_height/2, -mesh_length/2, 1.0f, 0.0f, 0.0f,
        mesh_width/2, mesh_height/2, -mesh_length/2, 0.0f, 1.0f, 0.0f,
        -mesh_width/2, -mesh_height/2, -mesh_length/2, 0.0f, 1.0f, 0.0f,
        mesh_width/2, -mesh_height/2, -mesh_length/2, 0.0f, 0.0f, 1.0f
    };

    const std::vector<short> indices
    {
        //Front face
        0, 1, 2,
        1, 3, 2,

        //Back face
        4, 5, 6,
        5, 7, 6,

        //Right face
        1, 5, 3,
        5, 7, 3,

        //Left face
        0, 4, 6,
        6, 2, 0,

        //Top face
        4, 5, 1,
        1, 0, 4,

        //Bottom face
        3, 7, 6,
        6, 2, 3,
    };

    Shader basicShader;
    const GLuint shaderProgram = basicShader.GetProgram();
    
    return Mesh(vertices, indices, shaderProgram, view, projection);
}

//Handles all common rendering operations, things that need to be done before drawing a mesh
void RenderLoop()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//TODO: refactor out all the preprocessor conditionals and logging to a separate class, maybe get spdlog
int main(int argc, char* argv[])
{
    glfwSetErrorCallback(LogGLFWErrors);
    glfwInit()

#ifdef PS_DEBUG
        == GLFW_TRUE ?
            std::cout << "GLFW initialized \n" : std::cout <<"GLFW failed to initialize \n";
#elif PS_RELEASE
    ;
#endif
    
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "My Super Cool Window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

#ifdef PS_DEBUG
    window == nullptr ? std::cout << "Failed to create window \n" : std::cout <<"Window successfully created \n";
#endif

    //Checking if glad is working or not
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))

#ifdef PS_DEBUG
        == false ?
            std::cout << "Failed to load GLAD \n" : std::cout <<"GLAD loaded successfully \n";
#elif PS_RELEASE
    ;
#endif

    glViewport(0, 0, window_width, window_height);
    if(resize_buffer)
        glfwSetFramebufferSizeCallback(window, ResizeWindow);

    Mesh mesh = CreateMesh();
    mesh.Translate(glm::vec3(-0.5, -0.5, -2));

    Mesh mesh2 = CreateMesh();
    mesh2.Translate(glm::vec3(-0.6, 0, 1));

    float angle = 0.0f;
    
    while (!glfwWindowShouldClose(window))
    {
        angle += 1;
        if(angle > 360) angle = 0.0f;
        
        glfwSwapBuffers(window);

        ProcessInput(window);

        RenderLoop();
        mesh.Rotate(angle, GLOBAL_UP_VECTOR);
        mesh.Draw();
        mesh2.Draw();
        
        glfwPollEvents();
    }
    
    glfwTerminate();
}