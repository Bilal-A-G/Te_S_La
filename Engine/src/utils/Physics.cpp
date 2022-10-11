#include "Physics.h"

#include "Logger.h"

float radius;

bool TESLA_PHYSICS::Raycaster::Raycast(glm::vec3 startPosition,
    glm::vec3 direction, float range, float resolution, const std::vector<TESLA::Model*>& sceneObjects, RaycastResult& result)
{
    const glm::vec3 normalizedDirection = glm::normalize(direction);
    
    for (int i = 0; i < resolution; i++)
    {
        glm::vec3 currentStep = startPosition + normalizedDirection * ((i/resolution) * range);
        for(TESLA::Model* model : sceneObjects)
        {
            for(const TESLA::Mesh& mesh : model->GetMeshes())
            {
                glm::vec3 diffVector = mesh.position - currentStep;
                
                if(glm::sqrt(diffVector.x * diffVector.x + diffVector.y * diffVector.y) <= radius)
                {
                    TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Hit {0}", model->name);
                    result = RaycastResult{model};
                    return  true;
                }
            }
        }
    }

    return false;
}

