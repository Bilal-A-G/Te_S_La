#pragma once
#include "../Model/Model.h"
#include "glm/glm.hpp"

namespace TESLA_PHYSICS
{
    struct RaycastResult
    {
        TESLA::Model* hitObject;    
    };
    
    class Raycaster
    {
    public:
        static bool Raycast(glm::vec3 startPosition, glm::vec3 direction, float range, float resolution, const std::vector<TESLA::Model*>& sceneObjects, RaycastResult& result);
    };
}
