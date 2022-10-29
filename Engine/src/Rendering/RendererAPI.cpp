#include "TSpch.h"
#include "RendererAPI.h"

#include "../Platform/OpenGL/OpenGLRendererAPI.h"

TESLA::API TESLA::RendererAPI::m_currentAPI;

TESLA::API TESLA::RendererAPI::GetCurrentAPI()
{
    return m_currentAPI;
}

TESLA::RendererAPI* TESLA::RendererAPI::Create()
{
    if(m_currentAPI == API::OpenGL)
    {
        return new OpenGLRendererAPI();
    }
}

