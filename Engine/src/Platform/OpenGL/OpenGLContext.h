#pragma once
#include "../../Rendering/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace TESLA
{
    class OpenGLContext : public TESLA::GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* window):
        m_window(window){}
        
        void Init() override;
        void SwapBuffers() override;
        void ResizeBuffer(int width, int height) override;
        void RenderLoop() override;
    private:
        GLFWwindow* m_window;
    };
}
