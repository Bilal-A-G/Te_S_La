#pragma once
#include <glm/vec4.hpp>

namespace TESLA
{
    class RenderCommand
    {
    public:
        static void Clear();
        static void SetClearColour(glm::vec4 colour);
    };
}
    
