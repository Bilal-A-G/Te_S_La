#pragma once

namespace TESLA
{
    struct Vertex
    {
        std::array<float, 3> position;
        std::array<float, 3> normal;
        std::array<float, 2> uv;
    };
    
    class Renderer
    {
    public:
        virtual ~Renderer(){}
        
        static void BeginScene();
        static void EndScene();
    };
    
}

