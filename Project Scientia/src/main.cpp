#include"glad/glad.h"
#include"GLFW/glfw3.h"

#include<iostream>

constexpr int window_height = 800;
constexpr int window_width = 1200;

void resize_window(GLFWwindow* window, int width, int height);

void log_glfw_errors(int id, const char* error_message);

void process_input(GLFWwindow* window);

//TODO: refactor out all the preprocessor conditionals and logging
int main(int argc, char* argv[])
{
    glfwSetErrorCallback(log_glfw_errors);
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
    
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))

#ifdef PS_DEBUG
    == false ?
        std::cout << "Failed to load GLAD \n" : std::cout <<"GLAD loaded successfully \n";
#elif PS_RELEASE
    ;
#endif

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, resize_window);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);

        process_input(window);

        glClearColor(0.4f, 0, 0.6f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
            
        glfwPollEvents();
    }

    glfwTerminate();
}

void resize_window(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}

void log_glfw_errors(int id, const char* error_message)
{
#ifdef PS_DEBUG
    std::cout << error_message << " ID = " << id << "\n";
#endif
}

void process_input(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
}



