#include "TSpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

TESLA::VertexBuffer* TESLA::VertexBuffer::Create()
{
    if constexpr (TESLA::Renderer::currentAPI == API::OpenGL)
    {
        return new OpenGLVertexBuffer();
    }
}

TESLA::ElementBuffer* TESLA::ElementBuffer::Create()
{
    if constexpr (TESLA::Renderer::currentAPI == API::OpenGL)
    {
        return new OpenGLElementBuffer();
    }
}

TESLA::ArrayBuffer* TESLA::ArrayBuffer::Create()
{
    if constexpr (TESLA::Renderer::currentAPI == API::OpenGL)
    {
        return new OpenGLArrayBuffer();
    }
}



