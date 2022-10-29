#include "TSpch.h"
#include "Shader.h"

#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLShader.h"

const char* defaultVertexShader = "../Engine/src/Rendering/DefaultShaders/vertex.glsl";
const char* defaultFragmentShader = "../Engine/src/Rendering/DefaultShaders/fragment.glsl";

TESLA::Shader* TESLA::Shader::Create(const char* vertexSource, const char* fragmentSource)
{
    if(TESLA::RendererAPI::GetCurrentAPI() == TESLA::API::OpenGL)
    {
        return new OpenGLShader(vertexSource, fragmentSource);
    }
}

TESLA::Shader* TESLA::Shader::Create()
{
    if(TESLA::RendererAPI::GetCurrentAPI() == TESLA::API::OpenGL)
    {
        return new OpenGLShader(defaultVertexShader, defaultFragmentShader);
    }
}


