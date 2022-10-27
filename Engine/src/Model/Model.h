#pragma once
#include "Mesh.h"
#include "assimp/scene.h"

namespace TESLA
{
    class Model
    {
    public:
        std::string name;
        Model(const Model& model)
            :m_viewMatrix(model.m_viewMatrix), m_projectionMatrix(model.m_projectionMatrix)
        {
            m_shaderProgram = model.m_shaderProgram;
            m_meshes = model.m_meshes;
            name = model.name;
        }
        
        Model(const char* fileName, const char* modelname, const int32_t& shaderProgram, glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
            : m_viewMatrix(viewMatrix), m_projectionMatrix(projectionMatrix)
        {
            m_shaderProgram = shaderProgram;
            name = modelname;

            LoadModel(fileName);
        }
    
        void Draw(glm::vec3 cameraPosition);

        void Translate(glm::vec3 translation);
        void Rotate(float angle, glm::vec3 upVector);
        void Scale(glm::vec3 scale);
        const std::vector<Mesh*>& GetMeshes(){return m_meshes;}
    
    private:
        void LoadModel(const char* fileName);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
    
        std::vector<Mesh*> m_meshes;

        int32_t m_shaderProgram;
    
        glm::mat4& m_viewMatrix;
        glm::mat4& m_projectionMatrix;
    };
}
