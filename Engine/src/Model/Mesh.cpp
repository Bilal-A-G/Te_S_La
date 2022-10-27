﻿#include "TSpch.h"
#include "Mesh.h"

#include "../Core/Application.h"
#include "glad/glad.h"

GLenum ShaderTypeToGLType(TESLA::ShaderDataType type)
{
    switch (type)
    {
        case TESLA::ShaderDataType::Float:      return GL_FLOAT;
        case TESLA::ShaderDataType::Float2:     return GL_FLOAT;
        case TESLA::ShaderDataType::Float3:     return GL_FLOAT;
        case TESLA::ShaderDataType::Float4:     return GL_FLOAT;
        case TESLA::ShaderDataType::Mat3:       return GL_FLOAT;
        case TESLA::ShaderDataType::Mat4:       return GL_FLOAT;
        case TESLA::ShaderDataType::Int:        return GL_INT;
        case TESLA::ShaderDataType::Int2:       return GL_INT;
        case TESLA::ShaderDataType::Int3:       return GL_INT;
        case TESLA::ShaderDataType::Int4:       return GL_INT;
        case TESLA::ShaderDataType::Bool:       return GL_BOOL;
        default:
            TS_LOG_ASSERTION(false, TESLA_LOGGER::ERR, "Unknown type");
    }
}

void TESLA::Mesh::SetupMesh()
{
    m_vao = TESLA::ArrayBuffer::Create();
    m_vao->Bind();

    m_vbo = TESLA::VertexBuffer::Create();
    m_ebo = TESLA::ElementBuffer::Create();
    
    m_vbo->Bind();
    m_vbo->UploadData(m_vertices.data(), sizeof(Vertex) * m_vertices.size());
    
    m_ebo->Bind();
    m_ebo->UploadData(m_indices.data(), sizeof(uint32_t) * m_indices.size());
    
    BufferLayout layout{
        {ShaderDataType::Float3, "position"},
        {ShaderDataType::Float3, "normal"},
        {ShaderDataType::Float2, "uv"},
    };
    
    m_vbo->SetLayout(layout);

    for(int i = 0;i < layout.GetElements().size();i++)
    {
        BufferElement element = layout.GetElements()[i];
        
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.GetComponentCount(), ShaderTypeToGLType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<const void*>(element.offset));
    }

    m_vao->UnBind();
    TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Sent to buffer: vertices = {0}, indices = {1}", m_vertices.size(), m_indices.size());
}

void TESLA::Mesh::Draw(glm::vec3 cameraPosition)
{
    glUseProgram(m_shaderProgram);
    UpdateMVPMatrix(cameraPosition);
    
    m_vao->Bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    m_vao->UnBind();
}

void TESLA::Mesh::Rotate(float angle, glm::vec3 upVector)
{
    m_rotationMatrix = glm::rotate(IDENTITY_MAT, glm::radians(angle), upVector);
}

void TESLA::Mesh::Scale(glm::vec3 scale)
{
    m_scaleMatrix = glm::scale(IDENTITY_MAT, scale);
}

void TESLA::Mesh::Translate(glm::vec3 translation)
{
    m_positionMatrix = glm::translate(IDENTITY_MAT, translation);
    position = translation;
}

void TESLA::Mesh::UpdateMVPMatrix(glm::vec3 cameraPosition)
{
    const GLint modelLocation = glGetUniformLocation(m_shaderProgram, "model");
    const GLint viewLocation = glGetUniformLocation(m_shaderProgram, "view");
    const GLint projectionLocation = glGetUniformLocation(m_shaderProgram, "projection");

    const GLint cameraLocation = glGetUniformLocation(m_shaderProgram, "cameraPosition");
    glUniform3f(cameraLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &(m_positionMatrix * m_rotationMatrix * m_scaleMatrix)[0][0]);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &m_viewMatrix[0][0]);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &m_projectionMatrix[0][0]);
}






