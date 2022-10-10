#pragma once
#include "Mesh.h"
#include "assimp/scene.h"

namespace TESLA
{
    class TS_DLL Model
    {
    public:
        Model(const char* fileName, const GLuint& shaderProgram, glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
            : m_viewMatrix(viewMatrix), m_projectionMatrix(projectionMatrix)
        {
            m_shaderProgram = shaderProgram;
            m_projectionMatrix = projectionMatrix;
            m_viewMatrix = viewMatrix;

            LoadModel(fileName);
        }
    
        void Draw();

        void Translate(glm::vec3 translation);
        void Rotate(float angle, glm::vec3 upVector);
        void Scale(glm::vec3 scale);
    
    private:
        void LoadModel(const char* fileName);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    
        std::vector<Mesh> m_meshes;

        GLuint m_shaderProgram;
    
        glm::mat4& m_viewMatrix;
        glm::mat4& m_projectionMatrix;
    };
}
