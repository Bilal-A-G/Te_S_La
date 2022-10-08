#pragma once
#include <windows.h>

#include "Mesh.h"
#include "assimp/scene.h"

class Model
{
public:
    Model(const char* fileName, const GLuint& shaderProgram, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
    {
        m_shaderProgram = shaderProgram;
        m_viewMatrix = viewMatrix;
        m_projectionMatrix = projectionMatrix;

        LoadModel(fileName);
    }
    
    void Draw();

    void Translate(glm::vec3 translation);
    void Rotate(float angle, glm::vec3 upVector);
    void Scale(glm::vec3 scale);
    
    const std::vector<Mesh>& GetMeshes(){ return m_meshes;}
private:
    void LoadModel(const char* fileName);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    
    std::vector<Mesh> m_meshes;

    GLuint m_shaderProgram;
    
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
};
