#pragma once
#include "glad/glad.h"

class shader
{
public:
    GLuint get_program();
private:
    GLuint compile_shader(const char* file_path, const GLenum type);
    GLuint create_shader_program(const GLuint* compiled_shaders);
};
