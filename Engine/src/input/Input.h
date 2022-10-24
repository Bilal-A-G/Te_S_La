#pragma once
#include <glm/vec2.hpp>
#include "../core/Core.h"

namespace TESLA
{
    class TS_DLL Input
    {
    public:
        static void Init();
        static void Update();
        static bool GetKeyDown(int keycode);
        static bool GetKeyHeld(const int& keycode);
        static bool GetKeyUp(const int& keycode);
        
        static bool GetMouseButtonDown(const int& keycode);
        static bool GetMouseButtonUp(const int& keycode);
        static bool GetMouseButtonHeld(const int& keycode);
        
        static glm::vec2 GetMousePosition();
        static void SetInputMode(const int& mode, const int& value);
        static float GetTime();
    };
}
