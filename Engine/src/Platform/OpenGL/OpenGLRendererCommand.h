#pragma once
#include <glm/vec4.hpp>

namespace TESLA
{
    class OpenGLRendererCommand
    {
    public:
        static void Clear();
        static void SetClearColour(glm::vec4 colour);
    };
}
