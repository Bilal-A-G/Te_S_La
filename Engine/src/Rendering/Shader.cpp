#include "TSpch.h"
#include "Shader.h"

namespace TESLA
{
    constexpr short num_shaders = 2;
    
    const char* vertex_shader_source_path = "../Engine/src/Rendering/DefaultShaders/vertex.glsl";
    const char* fragment_shader_source_path = "../Engine/src/Rendering/DefaultShaders/fragment.glsl";

int32_t Shader::GetProgram()
{
    int32_t compiled_shaders[num_shaders];
    compiled_shaders[0] = CompileShader(vertex_shader_source_path, GL_VERTEX_SHADER);
    compiled_shaders[1] = CompileShader(fragment_shader_source_path, GL_FRAGMENT_SHADER);

    const int32_t* array_ptr = compiled_shaders;

    return CreateShaderProgram(array_ptr);
}

int32_t Shader::CompileShader(const char* file_path, const GLenum type)
{
    std::ifstream shader_file;
    std::string shader_code;

    shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        std::string file_line;
        shader_file.open(file_path, std::ios::in);

        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();

        shader_file.close();
        shader_code = shader_stream.str();
    }
    catch (std::ifstream::failure &_)
    {
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to read from or open shader file");
    }
    
    const char* source;
    source = shader_code.c_str();

    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
#ifdef TS_DEBUG
    int success;
    const char* shader_type;
    
    switch (type)
    {
    case GL_VERTEX_SHADER:
        shader_type = "Vertex shader";
        break;
    case GL_FRAGMENT_SHADER:
        shader_type = "Fragment shader";
        break;
    default:
        shader_type = "Unknown shader";
        break;
    }
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infolog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infolog);
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to compile {0}: {1}", shader_type, infolog);
    }
    else
    {
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Compiled {0} successfully", shader_type);
    }
#endif
    return shader;
}

int32_t Shader::CreateShaderProgram(const int32_t* compiled_shaders)
{
    const GLuint shader_program = glCreateProgram();
    
    for (int i = 0; i < num_shaders; ++i)
    {
        glAttachShader(shader_program, *(compiled_shaders + i));
        glDeleteShader(*(compiled_shaders + i));
    }

    glLinkProgram(shader_program);

#ifdef TS_DEBUG
    int success;
    
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infolog[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, infolog);
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to link shader program: {1}", infolog);
    }
    else
    {
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Shader program successfully linked");
    }
#endif
    return shader_program;
}
    
}


