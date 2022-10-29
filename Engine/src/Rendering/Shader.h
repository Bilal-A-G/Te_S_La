#pragma once
#include <glm/mat4x4.hpp>

namespace TESLA
{
    class Shader
    {
    public:
        virtual ~Shader(){}
        
        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual uint32_t GetUniformLocation(const char* uniformName) = 0;
        virtual void UploadMatrix4(int32_t uniformLocation, glm::mat4 matrix) = 0;
        virtual void UploadVector3(int32_t uniformLocation, glm::vec3 vector) = 0;
        static Shader* Create(const char* vertexSource, const char* fragmentSource);
        static Shader* Create();
    protected:
        uint32_t m_shader;
    };
}
