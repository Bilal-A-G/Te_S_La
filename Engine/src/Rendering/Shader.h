#pragma once
#include "glad/glad.h"

namespace TESLA
{
    class Shader
    {
    public:
        int32_t GetProgram();
    private:
        int32_t CompileShader(const char* file_path, const GLenum type);
        int32_t CreateShaderProgram(const int32_t* compiled_shaders);
    };
}
