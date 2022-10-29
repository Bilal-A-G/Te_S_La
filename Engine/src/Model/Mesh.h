#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "../TSpch.h"
#include "../Rendering/Buffer.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Shader.h"

namespace TESLA
{

#define IDENTITY_MAT glm::mat4(1.0f)

    class Mesh
    {
    public:
        glm::vec3 position = glm::vec3(0);
        
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, TESLA::Shader* shader, glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
            : m_viewMatrix(viewMatrix), m_projectionMatrix(projectionMatrix)
        {
            m_vertices = vertices;
            m_indices = indices;
            m_shader = shader;
            
            this->SetupMesh();
        }

        Mesh& operator=(const Mesh& mesh)
        {
            m_vao = mesh.m_vao;
            return *this;
        }

        ~Mesh()
        {
            delete m_ebo;
            delete m_vao;
            delete m_vbo;

            m_ebo = nullptr;
            m_vao = nullptr;
            m_vbo = nullptr;
        }
    
        void Draw(glm::vec3 cameraPosition);
        void Translate(glm::vec3 translation);
        void Rotate(float angle, glm::vec3 upVector);
        void Scale(glm::vec3 scale);
    private:
        void SetupMesh();
        void UpdateMVPMatrix(glm::vec3 cameraPosition);
    
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        TESLA::Shader* m_shader;
        
        TESLA::ArrayBuffer* m_vao;
        TESLA::VertexBuffer* m_vbo;
        TESLA::ElementBuffer* m_ebo;

        glm::mat4 m_scaleMatrix = IDENTITY_MAT;
        glm::mat4 m_rotationMatrix = IDENTITY_MAT;
        glm::mat4 m_positionMatrix = IDENTITY_MAT;
    
        glm::mat4& m_viewMatrix;
        glm::mat4& m_projectionMatrix;
    };
}

