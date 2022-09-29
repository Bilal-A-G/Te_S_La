﻿// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppMemberFunctionMayBeConst
#include "shader.h"
#include <fstream>
#include <sstream>
#include <string>
#ifdef PS_DEBUG
#include <iostream>
#endif

constexpr short num_shaders = 2;
const char* vertex_shader_source_path = "./src/shader_src/vertex.glsl";
const char* fragment_shader_source_path = "./src/shader_src/fragment.glsl";

GLuint shader::get_program()
{
    GLuint compiled_shaders[num_shaders];
    compiled_shaders[0] = compile_shader(vertex_shader_source_path, GL_VERTEX_SHADER);
    compiled_shaders[1] = compile_shader(fragment_shader_source_path, GL_FRAGMENT_SHADER);

    const GLuint* array_ptr = compiled_shaders;

    return create_shader_program(array_ptr);
}


GLuint shader::compile_shader(const char* file_path, const GLenum type)
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
#ifdef PS_DEBUG
        std::cout << "Failed to read from or open file \n";
#endif
    }
    
    const char* source;
    source = shader_code.c_str();

    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
#ifdef PS_DEBUG
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
        std::cout << shader_type << " failed to compile " << infolog << "\n";
    }
    else
    {
        std::cout << shader_type << " successfully compiled " << "\n";
    }
#endif
    return shader;
}


GLuint shader::create_shader_program(const GLuint* compiled_shaders)
{
    const GLuint shader_program = glCreateProgram();
    
    for (int i = 0; i < num_shaders; ++i)
    {
        glAttachShader(shader_program, *(compiled_shaders + i));
        glDeleteShader(*(compiled_shaders + i));
    }

    glLinkProgram(shader_program);

#ifdef PS_DEBUG
    int success;
    
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infolog[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, infolog);
        std::cout << "Shader program failed to link " << infolog << "\n";
    }
    else
    {
        std::cout << "Shader program successfully linked " << "\n";
    }
#endif
    return shader_program;
}


