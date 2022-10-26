#pragma once
namespace TESLA
{
    enum class ShaderDataType
    {
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static uint32_t ShaderDataSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 8;
            case ShaderDataType::Float3: return 12;
            case ShaderDataType::Float4: return 16;
            case ShaderDataType::Mat3:   return 36;
            case ShaderDataType::Mat4:   return 64;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 8;
            case ShaderDataType::Int3:   return 12;
            case ShaderDataType::Int4:   return 16;
            case ShaderDataType::Bool:   return 1;
            default:
                TS_LOG_ASSERTION(false, TESLA_LOGGER::ERR, "Unknown shader data type");
                return NULL;
        }
    }

    struct BufferElement
    {
        std::string name;
        uint32_t size;
        uint32_t offset;
        ShaderDataType type;
        bool normalized;

        BufferElement(){}
        
        BufferElement(ShaderDataType type, const std::string& name):
        name(name), type(type), size(ShaderDataSize(type)), offset(0), normalized(false){}

        uint32_t GetComponentCount() const
        {
            switch (type)
            {
            case ShaderDataType::Float:  return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Mat3:   return 9;
            case ShaderDataType::Mat4:   return 16;
            case ShaderDataType::Int:    return 1;
            case ShaderDataType::Int2:   return 2;
            case ShaderDataType::Int3:   return 3;
            case ShaderDataType::Int4:   return 4;
            case ShaderDataType::Bool:   return 1;
            default:
                TS_LOG_ASSERTION(false, TESLA_LOGGER::ERR, "Unknown shader data type");
                return NULL;
            }
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout(){}
        
        BufferLayout(const std::initializer_list<BufferElement>& elements):
        m_elements(elements)
        {
            CalculateOffsetsAndStride();
        }
        uint32_t GetStride(){return m_stride;}

        const std::vector<BufferElement>& GetElements(){return m_elements;}
    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_stride = 0;
            
            for(BufferElement& element : m_elements)
            {
                element.offset = offset;
                offset += element.size;
                m_stride += element.size;
            }
        }
        std::vector<BufferElement> m_elements;
        uint32_t m_stride;
    };
    
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer(){}

        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual void UploadData(void* vertices, uint32_t size) = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() = 0;
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
