#pragma once
#include "../../Rendering/Buffer.h"

namespace TESLA
{
    class OpenGLVertexBuffer : public TESLA::VertexBuffer
    {
    public:
        OpenGLVertexBuffer();
        ~OpenGLVertexBuffer();
        void Bind() override;
        void UnBind() override;
        void UploadData(void* vertices, uint32_t size) override;

    private:
        uint32_t* m_bufferObject;
    };

    class OpenGLElementBuffer : public TESLA::ElementBuffer
    {
    public:
        OpenGLElementBuffer();
        ~OpenGLElementBuffer();
        void Bind() override;
        void UnBind() override;
        void UploadData(uint32_t* indices, uint32_t size) override;
    private:
        uint32_t* m_bufferObject;
    };

    class OpenGLArrayBuffer : public TESLA::ArrayBuffer
    {
    public:
        OpenGLArrayBuffer();
        ~OpenGLArrayBuffer();
        void Bind() override;
        void UnBind() override;
    private:
        uint32_t* m_bufferObject;
    };

}
