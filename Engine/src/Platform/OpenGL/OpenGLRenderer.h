#pragma once
#include "../../Model/Mesh.h"
#include "../../Rendering/Renderer.h"

namespace TESLA
{
    class OpenGLRenderer : public TESLA::Renderer
    {
    public:
        int ShaderTypeToGLType(TESLA::ShaderDataType type) override;
        void BeginScene() override;
        void EndScene() override;
    };
}
