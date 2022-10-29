#pragma once
#include <glm/vec4.hpp>
#include "Renderer.h"

namespace TESLA
{
    class RenderCommand
    {
    public:
        static void Clear();
        static void SetClearColour(glm::vec4 colour);
        static void Draw(std::vector<TESLA::Vertex>& vertices, std::vector<uint32_t>& indices);
    };
}
    
