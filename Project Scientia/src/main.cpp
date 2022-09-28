#include"glad/glad.h"
#include"GLFW/glfw3.h"

#include<iostream>

constexpr int window_height = 800;
constexpr int window_width = 1200;

constexpr float mesh_size = 0.5f;

void resize_window(GLFWwindow* window, int width, int height);
void log_glfw_errors(int id, const char* error_message);
void process_input(GLFWwindow* window);
void draw_mesh();
GLuint compile_shaders();
void render_mesh();

const char* vertex_shader_source = R"(
#version 330 core
layout {location = 0} in vec3 position;
void main()
{
    gl_position = vec4(position.x, position.y, position.z, 0.0f);
}
)";

const char*  fragment_shader_source = R"(
#version 330 core
out vec4 frag_colour;
void main()
{
    frag_colour = vec4(0.6f, 0.0f, 0.5f, 1.0f);
}
)";

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
    glUseProgram(compile_shaders());
    draw_mesh();

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

void draw_mesh()
{
    GLuint vbo;

    constexpr float vertices[]
    {
        0.0f, mesh_size/2,
        -mesh_size/2, -mesh_size/2,
        mesh_size/2, -mesh_size/2
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

GLuint compile_shaders()
{
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);

    const GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

#ifdef PS_DEBUG
    char infolog[512];
    int success;
    
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, infolog);
        std::cout << "Vertex shader failed to compile " << infolog << "\n";
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, infolog);
        std::cout << "Fragment shader failed to compile " << infolog << "\n";
    }
#endif
    
    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);
    
    return shader_program;
}

void render_mesh()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}






