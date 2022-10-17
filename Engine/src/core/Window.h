#pragma once
#include "../core/Core.h"
#include "../utils/events/Event.h"
#include "GLFW/glfw3.h"

namespace TESLA
{
    struct WindowProperties
    {
        int width, height;
        std::string name;

        WindowProperties(const int& width, const int& height, const char* name)
            :width(width), height(height), name(name){}
    };
    
    class TS_DLL Window
    {
    public:
        virtual void Update() = 0;
        virtual int GetHeight() = 0;
        virtual int GetWidth() = 0;
        virtual std::string GetName() = 0;

        virtual void SetVSync(const bool& set) = 0;
        virtual bool GetVSync() = 0;

        virtual void InitImGUI() = 0;
        virtual bool WindowShouldClose() = 0;
        virtual void SetInputMode(int mode, int value) = 0;
    
        static Window* Create(const WindowProperties& properties);
        static Window* Create(const char* name){return Create({1200, 800, name});}
    };

}
