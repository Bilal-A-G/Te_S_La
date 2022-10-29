#pragma once

namespace TESLA
{
    enum API
    {
        OpenGL
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
    
    class RendererAPI
    {
    public:
        static API GetCurrentAPI();
        virtual int ShaderTypeToGLType(TESLA::ShaderDataType type) = 0;

        static RendererAPI* Create();
    private:
        static TESLA::API m_currentAPI;
    };
}
