#pragma once

namespace TESLA
{
    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
        virtual void ResizeBuffer(int width, int height) = 0;
    };
}
