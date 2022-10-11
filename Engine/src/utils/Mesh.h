#pragma once
#include <array>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "glad/glad.h"
#include "../core/core.h"

//This class handles per mesh data/operations

namespace TESLA
{

#define IDENTITY_MAT glm::mat4(1.0f)
    
    struct TS_DLL Vertex
    {
        std::array<float, 3> position;
        std::array<float, 3> normal;
        std::array<float, 2> uv;
    };

    class TS_DLL Mesh
    {
    public:
        glm::vec3 position = glm::vec3(0);
        
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const GLuint& shaderProgram, glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
            : m_viewMatrix(viewMatrix), m_projectionMatrix(projectionMatrix)
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
    
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        GLuint m_shaderProgram;
        GLuint m_vao;

        glm::mat4 m_scaleMatrix = IDENTITY_MAT;
        glm::mat4 m_rotationMatrix = IDENTITY_MAT;
        glm::mat4 m_positionMatrix = IDENTITY_MAT;
    
        glm::mat4& m_viewMatrix;
        glm::mat4& m_projectionMatrix;
    };
}

