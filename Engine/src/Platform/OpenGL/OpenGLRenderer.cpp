#include "TSpch.h"
#include "OpenGLRenderer.h"

#include "glad/glad.h"

int TESLA::OpenGLRenderer::ShaderTypeToGLType(TESLA::ShaderDataType type)
{
    switch (type)
    {
    case TESLA::ShaderDataType::Float:      return GL_FLOAT;
    case TESLA::ShaderDataType::Float2:     return GL_FLOAT;
    case TESLA::ShaderDataType::Float3:     return GL_FLOAT;
    case TESLA::ShaderDataType::Float4:     return GL_FLOAT;
    case TESLA::ShaderDataType::Mat3:       return GL_FLOAT;
    case TESLA::ShaderDataType::Mat4:       return GL_FLOAT;
    case TESLA::ShaderDataType::Int:        return GL_INT;
    case TESLA::ShaderDataType::Int2:       return GL_INT;
    case TESLA::ShaderDataType::Int3:       return GL_INT;
    case TESLA::ShaderDataType::Int4:       return GL_INT;
    case TESLA::ShaderDataType::Bool:       return GL_BOOL;
    default:
        TS_LOG_ASSERTION(false, TESLA_LOGGER::ERR, "Unknown type");
        return 0;
    }
}

void TESLA::OpenGLRenderer::Draw(std::vector<TESLA::Vertex>& vertices, std::vector<uint32_t>& indices)
{
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

void TESLA::OpenGLRenderer::Clear()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TESLA::OpenGLRenderer::BeginScene()
{
    
}

void TESLA::OpenGLRenderer::EndScene()
{
    
}




