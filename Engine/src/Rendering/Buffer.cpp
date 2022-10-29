#include "TSpch.h"
#include "Buffer.h"

#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

TESLA::VertexBuffer* TESLA::VertexBuffer::Create()
{
    if (TESLA::RendererAPI::GetCurrentAPI() == API::OpenGL)
    {
        return new OpenGLVertexBuffer();
    }
}

TESLA::ElementBuffer* TESLA::ElementBuffer::Create()
{
    if (TESLA::RendererAPI::GetCurrentAPI() == API::OpenGL)
    {
        return new OpenGLElementBuffer();
    }
}

TESLA::ArrayBuffer* TESLA::ArrayBuffer::Create()
{
    if (TESLA::RendererAPI::GetCurrentAPI() == API::OpenGL)
    {
        return new OpenGLArrayBuffer();
    }
}



