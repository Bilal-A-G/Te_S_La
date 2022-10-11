#pragma once
#include <glm/glm.hpp>
#include "GLFW/glfw3.h"

class Camera
{
public:
    static glm::mat4 CalculateView(GLFWwindow* window);
};
