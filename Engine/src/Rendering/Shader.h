#pragma once
#include "glad/glad.h"

namespace TESLA
{
    class Shader
    {
    public:
        GLuint GetProgram();
    private:
        GLuint CompileShader(const char* file_path, const GLenum type);
        GLuint CreateShaderProgram(const GLuint* compiled_shaders);
    };
}
