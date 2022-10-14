#pragma once
#include "glad/glad.h"
#include "../../core/Core.h"

//This class handles everything to do with shaders

namespace TESLA
{
    class TS_DLL Shader
    {
    public:
        GLuint GetProgram();
    private:
        GLuint CompileShader(const char* file_path, const GLenum type);
        GLuint CreateShaderProgram(const GLuint* compiled_shaders);
    };
}
