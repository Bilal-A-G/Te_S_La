#pragma once
#include "../../Rendering/Buffer.h"
#include "../../Rendering/Renderer.h"

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

        BufferLayout& GetLayout() override
        {
            return m_layout;
        };
        void SetLayout(const BufferLayout& layout) override
        {
            m_layout = layout;
        };
    private:
        uint32_t* m_bufferObject;
        BufferLayout m_layout;
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
        void SetVertexLayout(VertexBuffer* buffer, TESLA::RendererAPI* renderer) override;
    private:
        uint32_t* m_bufferObject;
    };

}
