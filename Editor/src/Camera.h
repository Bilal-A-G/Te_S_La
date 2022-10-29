﻿#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    static void Init();
    static glm::mat4 CalculateView();
public:
    inline static glm::vec3 cameraPosition = glm::vec3(1.5f, 1.0f, 1.5f);
    inline static glm::vec3 cameraDirection;
};
