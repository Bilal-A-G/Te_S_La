#include "TSpch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"

TESLA::OpenGLVertexBuffer::OpenGLVertexBuffer()
{
    m_bufferObject = new uint32_t();
    glGenBuffers(1, m_bufferObject);
}

TESLA::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, m_bufferObject);
    delete m_bufferObject;
    m_bufferObject = nullptr;
}

void TESLA::OpenGLVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, *m_bufferObject);
}

void TESLA::OpenGLVertexBuffer::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TESLA::OpenGLVertexBuffer::UploadData(void* vertices, uint32_t size)
{
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}


TESLA::OpenGLElementBuffer::OpenGLElementBuffer()
{
    m_bufferObject = new uint32_t();
    glGenBuffers(1, m_bufferObject);
}

TESLA::OpenGLElementBuffer::~OpenGLElementBuffer()
{
    glDeleteBuffers(1, m_bufferObject);
    delete(m_bufferObject);
    m_bufferObject = nullptr;
}

void TESLA::OpenGLElementBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_bufferObject);
}

void TESLA::OpenGLElementBuffer::UnBind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TESLA::OpenGLElementBuffer::UploadData(uint32_t* indices, uint32_t size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}



TESLA::OpenGLArrayBuffer::OpenGLArrayBuffer()
{
    m_bufferObject = new uint32_t();
    glGenVertexArrays(1, m_bufferObject);
}

TESLA::OpenGLArrayBuffer::~OpenGLArrayBuffer()
{
    glDeleteVertexArrays(1, m_bufferObject);
    delete(m_bufferObject);
    m_bufferObject = nullptr;
}

void TESLA::OpenGLArrayBuffer::Bind()
{
    glBindVertexArray(*m_bufferObject);
}

void TESLA::OpenGLArrayBuffer::UnBind()
{
    glBindVertexArray(0);
}

void TESLA::OpenGLArrayBuffer::SetVertexLayout(VertexBuffer* buffer, TESLA::Renderer* renderer)
{
    BufferLayout& layout = buffer->GetLayout();
    for(int i = 0;i < layout.GetElements().size();i++)
    {
        BufferElement element = layout.GetElements()[i];
        
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.GetComponentCount(), renderer->ShaderTypeToGLType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<const void*>(element.offset));
    }

}







