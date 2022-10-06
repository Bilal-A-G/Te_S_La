#pragma once
#include <array>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "glad/glad.h"

//This class handles per mesh data/operations

#define IDENTITY_MAT glm::mat4(1.0f)

struct Vertex
{
    std::array<float, 3> position;
    std::array<float, 3> colour;
};

class Mesh
{
public:
    Mesh(const std::vector<float> &vertices, const std::vector<short> &indices, const GLuint& shaderProgram, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
    {
        m_vertices = vertices;
        m_indices = indices;
        m_shaderProgram = shaderProgram;
        m_projectionMatrix = projectionMatrix;
        m_viewMatrix = viewMatrix;
        this->SetupGLObjects();
    }
    
    void Draw();
    void Translate(glm::vec3 translation);
    void Rotate(float angle, glm::vec3 upVector);
    void Scale(glm::vec3 scale);
    
    const GLuint GetShaderProgram()
    {
        return m_shaderProgram;
    }
private:
    void SetupGLObjects();
    void UpdateMVPMatrix();
    
    std::vector<float> m_vertices;
    std::vector<short> m_indices;
    GLuint m_shaderProgram;
    GLuint m_vao;

    glm::mat4 m_scaleMatrix = IDENTITY_MAT;
    glm::mat4 m_rotationMatrix = IDENTITY_MAT;
    glm::mat4 m_positionMatrix = IDENTITY_MAT;
    
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
};
