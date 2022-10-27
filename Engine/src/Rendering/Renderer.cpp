#include "TSpch.h"
#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLRenderer.h"

TESLA::Renderer* TESLA::Renderer::Create()
{
    if constexpr (TESLA::Renderer::currentAPI == API::OpenGL)
    {
        return new OpenGLRenderer();
    }
}

