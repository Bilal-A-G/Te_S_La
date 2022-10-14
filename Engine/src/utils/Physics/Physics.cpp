#include "Physics.h"

#include "../Logging/Logger.h"

float radius = 1;

bool TESLA_PHYSICS::Raycaster::Raycast(glm::vec3 startPosition,
    glm::vec3 direction, float range, float resolution, const std::vector<TESLA::Model*>& sceneObjects, RaycastResult& result)
{
    for (int i = 0; i < resolution; i++)
    {
        glm::vec3 currentStep = startPosition + direction * ((i/resolution) * range);
        for(TESLA::Model* model : sceneObjects)
        {
            for(const TESLA::Mesh& mesh : model->GetMeshes())
            {
                glm::vec3 diffVector = mesh.position - currentStep;
                
                if(glm::sqrt(diffVector.x * diffVector.x + diffVector.y * diffVector.y) <= radius)
                {
                    result = RaycastResult{model};
                    return  true;
                }
            }
        }
    }

    return false;
}

