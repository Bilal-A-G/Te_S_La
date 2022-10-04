#include "shader.h"
#include"GLFW/glfw3.h"

#include<iostream>
#include <glm/gtc/matrix_transform.hpp>

int window_height = 800;
int window_width = 1200;

constexpr float mesh_width = 1.0f;
constexpr float mesh_height = 1.0f;
constexpr float mesh_length = 1.0f;

constexpr bool resize_buffer = true;

void resize_window(GLFWwindow* window, int width, int height);
void log_glfw_errors(int id, const char* error_message);
void process_input(GLFWwindow* window);
GLuint draw_mesh();
GLuint compile_shaders();
void render_mesh();

//TODO: refactor out all the preprocessor conditionals and logging
int main(int argc, char* argv[]);


void resize_window(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
    window_height = height;
    window_width = width;
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
        -mesh_width/2, mesh_height/2, mesh_length/2, 1.0f, 0.0f, 0.0f,
        mesh_width/2, mesh_height/2, mesh_length/2, 0.0f, 1.0f, 0.0f,
        -mesh_width/2, -mesh_height/2, mesh_length/2, 0.0f, 1.0f, 0.0f,
        mesh_width/2, -mesh_height/2, mesh_length/2, 0.0f, 0.0f, 1.0f,

        -mesh_width/2, mesh_height/2, -mesh_length/2, 1.0f, 0.0f, 0.0f,
        mesh_width/2, mesh_height/2, -mesh_length/2, 0.0f, 1.0f, 0.0f,
        -mesh_width/2, -mesh_height/2, -mesh_length/2, 0.0f, 1.0f, 0.0f,
        mesh_width/2, -mesh_height/2, -mesh_length/2, 0.0f, 0.0f, 1.0f
    };

    constexpr unsigned short int vertex_indices[] =
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
    
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
    
    return vao;
}

void render_mesh()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_SHORT, nullptr);
}

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
    if(resize_buffer)
        glfwSetFramebufferSizeCallback(window, resize_window);

    const glm::mat4 projection = glm::perspective(glm::radians(50.0f), static_cast<float>(window_width)/static_cast<float>(window_height), 0.1f, 100.0f);
    const glm::mat4 view = glm::lookAt(
        glm::vec3(1, 1, 1),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    
    glm::mat4 model = glm::mat4(1.0f);

    const glm::mat4 scale = glm::mat4(
        0.8, 0, 0, 0,
        0, 0.8, 0, 0,
        0, 0, 0.8, 0,
        0, 0, 0, 1
    );
    const glm::mat4 translation = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    const glm::mat4 rotation = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));

    model = translation * rotation * scale * model;
    
    glm::mat4 mvp = projection * view * model;
    
    shader shader_manager;
    const GLuint shader_program = shader_manager.get_program();
    
    glUseProgram(shader_program);
    
    glBindVertexArray(draw_mesh());

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);

        process_input(window);
        
        const GLint mvp_location = glGetUniformLocation(shader_program, "MVP");
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
        
        render_mesh();
        
        glfwPollEvents();
    }

    glfwTerminate();
}






