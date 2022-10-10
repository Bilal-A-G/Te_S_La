#pragma once
#include <glm/glm.hpp>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class CameraMovement
{
public:
    static glm::mat4 Look(GLFWwindow* window);
};
