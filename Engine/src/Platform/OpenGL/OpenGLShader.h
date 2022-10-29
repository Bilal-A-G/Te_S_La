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
        void UploadMatrix4(int32_t uniformLocation, glm::mat4 matrix) override;
        void UploadVector3(int32_t uniformLocation, glm::vec3 vector) override;
    };
}
    
