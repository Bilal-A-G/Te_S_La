#pragma once

namespace TESLA
{
    enum API
    {
        OpenGL
    };
    
    class RendererAPI
    {
    public:
        static API GetCurrentAPI();
    private:
        static TESLA::API m_currentAPI;
    };
}
