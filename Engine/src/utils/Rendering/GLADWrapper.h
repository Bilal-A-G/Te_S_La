#pragma once
#include "../../core/Core.h"

namespace TESLA
{
    class TS_DLL GLADWrapper
    {
    public:
        static void OpenGLRender();
        static bool LoadGLAD(void* test);
        static void UpdateViewport(const int &width, const int &height);
    };
}
