#pragma once
#include "../../Rendering/Shader.h"

namespace TESLA
{
    class OpenGLShader : public TESLA::Shader
    {
    public:
        OpenGLShader(const char* vertexShader, const char* fragmentShader);
        void Bind() override;
        void UnBind() override;
        uint32_t GetUniformLocation(const char* uniformName) override;
    };
}
    
