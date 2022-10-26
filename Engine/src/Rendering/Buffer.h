#pragma once
namespace TESLA
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer(){}

        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual void UploadData(void* vertices, uint32_t size) = 0;
        
        static VertexBuffer* Create();
    };

    class ElementBuffer
    {
    public:
        virtual ~ElementBuffer(){}

        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual void UploadData(uint32_t* indices, uint32_t size) = 0;
        
        static ElementBuffer* Create();
    };

    class ArrayBuffer
    {
    public:
        virtual ~ArrayBuffer(){}

        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        
        static ArrayBuffer* Create();
    };
}
