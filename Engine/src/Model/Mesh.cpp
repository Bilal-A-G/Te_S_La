#include "TSpch.h"
#include "Mesh.h"

#include "../Core/Application.h"
#include "glad/glad.h"

void TESLA::Mesh::SetupMesh()
{
    m_vao = TESLA::ArrayBuffer::Create();

    m_vao->Bind();

    TESLA::Application::GetVBO()->Bind();
    TESLA::Application::GetVBO()->UploadData(m_vertices.data(), sizeof(Vertex) * m_vertices.size());
    
    TESLA::Application::GetEBO()->Bind();
    TESLA::Application::GetEBO()->UploadData(m_indices.data(), sizeof(Vertex) * m_vertices.size());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Sent to buffer: vertices = {0}, indices = {1}", m_vertices.size(), m_indices.size());

    m_vao->UnBind();
}

void TESLA::Mesh::Draw()
{
    glUseProgram(m_shaderProgram);
    UpdateMVPMatrix();
    
    m_vao->Bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
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

void TESLA::Mesh::UpdateMVPMatrix()
{
    const GLint modelLocation = glGetUniformLocation(m_shaderProgram, "model");
    const GLint viewLocation = glGetUniformLocation(m_shaderProgram, "view");
    const GLint projectionLocation = glGetUniformLocation(m_shaderProgram, "projection");
    
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &(m_positionMatrix * m_rotationMatrix * m_scaleMatrix)[0][0]);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &m_viewMatrix[0][0]);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &m_projectionMatrix[0][0]);

}






