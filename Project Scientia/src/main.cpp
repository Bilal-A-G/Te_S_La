#include "shader.h"
#include"GLFW/glfw3.h"

#include<iostream>

constexpr int window_height = 800;
constexpr int window_width = 1200;

constexpr float mesh_width = 1.0f;
constexpr float mesh_height = 1.5f;

void resize_window(GLFWwindow* window, int width, int height);
void log_glfw_errors(int id, const char* error_message);
void process_input(GLFWwindow* window);
GLuint draw_mesh();
GLuint compile_shaders();
void render_mesh();

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
    shader shader_manager;
    
    glUseProgram(shader_manager.get_program());
    glBindVertexArray(draw_mesh());

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);

        process_input(window);
        render_mesh();
        
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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

GLuint draw_mesh()
{
    GLuint vao;
    
    GLuint vbo;
    GLuint ebo;

    constexpr float vertices[]
    {
        0.0f, mesh_height/2, 0.0f, 0.0f, 0.0f,
        -mesh_width/2, 0.0f, 0.0f, 1.0f, 0.0f,
        mesh_width/2, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, -mesh_height/2, 1.0f, 1.0f, 1.0f,
    };

    constexpr unsigned short int vertex_indices[] =
    {
        0, 1, 2,
        1, 2, 3
    };
    
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 2));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
    
    return vao;
}

void render_mesh()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}






