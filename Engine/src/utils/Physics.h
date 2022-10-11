#pragma once
#include "Model.h"
#include "glm/glm.hpp"
#include"../core/Core.h"

namespace TESLA_PHYSICS
{
    struct RaycastResult
    {
        TESLA::Model* hitObject;    
    };
    
    class TS_DLL Raycaster
    {
    public:
        static bool Raycast(glm::vec3 startPosition, glm::vec3 direction, float range, float resolution, const std::vector<TESLA::Model*>& sceneObjects, RaycastResult& result);
    };
}
