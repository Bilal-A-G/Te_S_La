#include "TSpch.h"
#include "Buffer.h"

#include "../Platform/OpenGL/OpenGLBuffer.h"

enum API
{
    OpenGL
};

constexpr API currentAPI = API::OpenGL;

TESLA::VertexBuffer* TESLA::VertexBuffer::Create()
{
    if constexpr (currentAPI == API::OpenGL)
    {
        return new OpenGLVertexBuffer();
    }
}

TESLA::ElementBuffer* TESLA::ElementBuffer::Create()
{
    if constexpr (currentAPI == API::OpenGL)
    {
        return new OpenGLElementBuffer();
    }
}

TESLA::ArrayBuffer* TESLA::ArrayBuffer::Create()
{
    if constexpr (currentAPI == API::OpenGL)
    {
        return new OpenGLArrayBuffer();
    }
}



