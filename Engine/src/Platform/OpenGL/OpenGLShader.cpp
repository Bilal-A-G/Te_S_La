#include "TSpch.h"
#include "OpenGLShader.h"
#include "glad/glad.h"

int32_t CompileShader(const char* file_path, const GLenum type);
int32_t CreateShaderProgram(const std::array<uint32_t, 2>& compiledShaders);

TESLA::OpenGLShader::OpenGLShader(const char* vertexShader, const char* fragmentShader)
{
    const uint32_t compiledVertexShader = CompileShader(vertexShader, GL_VERTEX_SHADER);
    const uint32_t compiledFragmentShader = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    m_shader = CreateShaderProgram({compiledVertexShader, compiledFragmentShader});
}

void TESLA::OpenGLShader::Bind()
{
    glUseProgram(m_shader);
}

void TESLA::OpenGLShader::UnBind()
{
    glUseProgram(0);
}

uint32_t TESLA::OpenGLShader::GetUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(m_shader, uniformName);
}


int32_t CompileShader(const char* file_path, const GLenum type)
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

int32_t CreateShaderProgram(const std::array<uint32_t, 2>& compiledShaders)
{
    const GLuint shaderProgram = glCreateProgram();
    
    for (int i = 0; i < compiledShaders.size(); ++i)
    {
        glAttachShader(shaderProgram, compiledShaders[i]);
        glDeleteShader(compiledShaders[i]);
    }

    glLinkProgram(shaderProgram);

#ifdef TS_DEBUG
    int success;
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infolog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infolog);
        TS_LOG_MESSAGE(TESLA_LOGGER::ERR, "Failed to link shader program: {1}", infolog);
    }
    else
    {
        TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Shader program successfully linked");
    }
#endif
    return shaderProgram;
}


