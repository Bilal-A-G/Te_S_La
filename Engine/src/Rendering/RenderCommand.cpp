#include "TSpch.h"
#include "RenderCommand.h"

#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLRendererCommand.h"

void TESLA::RenderCommand::Clear()
{
    if(TESLA::RendererAPI::GetCurrentAPI() == TESLA::API::OpenGL)
    {
        TESLA::OpenGLRendererCommand::Clear();
    }
}

void TESLA::RenderCommand::SetClearColour(glm::vec4 colour)
{
    if(TESLA::RendererAPI::GetCurrentAPI() == TESLA::API::OpenGL)
    {
        TESLA::OpenGLRendererCommand::SetClearColour(colour);
    }
}

void TESLA::RenderCommand::Draw(std::vector<TESLA::Vertex>& vertices, std::vector<uint32_t>& indices)
{
    if(TESLA::RendererAPI::GetCurrentAPI() == TESLA::API::OpenGL)
    {
        TESLA::OpenGLRendererCommand::Draw(vertices, indices);
    }
}


