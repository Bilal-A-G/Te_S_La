#include "TSpch.h"
#include "Renderer.h"

#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLRenderer.h"

TESLA::Renderer* TESLA::Renderer::Create()
{
    if (TESLA::RendererAPI::GetCurrentAPI() == API::OpenGL)
    {
        return new OpenGLRenderer();
    }
}

