#pragma once
#include "../../Rendering/RendererAPI.h"

namespace TESLA
{
    class OpenGLRendererAPI : public TESLA::RendererAPI
    {
    public:
        int ShaderTypeToGLType(TESLA::ShaderDataType type) override;
    };
}
