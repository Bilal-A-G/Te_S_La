#pragma once
#include "../../Model/Mesh.h"
#include "../../Rendering/Renderer.h"

namespace TESLA
{
    class OpenGLRenderer : public TESLA::Renderer
    {
    public:
        void Draw(std::vector<TESLA::Vertex>& vertices, std::vector<uint32_t>& indices) override;
        int ShaderTypeToGLType(TESLA::ShaderDataType type) override;
        void BeginScene() override;
        void EndScene() override;
    };
}
