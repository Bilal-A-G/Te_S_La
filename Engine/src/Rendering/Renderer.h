#pragma once

namespace TESLA
{
    enum API
    {
        OpenGL
    };

    struct Vertex
    {
        std::array<float, 3> position;
        std::array<float, 3> normal;
        std::array<float, 2> uv;
    };

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
    
    class Renderer
    {
    public:
        static constexpr TESLA::API currentAPI = TESLA::API::OpenGL;
        virtual ~Renderer(){}
        
        virtual void Draw(std::vector<TESLA::Vertex>& vertices, std::vector<uint32_t>& indices) = 0;
        virtual int ShaderTypeToGLType(TESLA::ShaderDataType type) = 0;
        virtual void Clear() = 0;
        virtual void BeginScene() = 0;
        virtual void EndScene() = 0;
        static Renderer* Create();
    };
    
}

