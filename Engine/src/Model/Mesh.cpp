#include "TSpch.h"
#include "Mesh.h"
#include "../Core/Application.h"
#include "../Rendering/RenderCommand.h"

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
    m_vao->SetVertexLayout(m_vbo, TESLA::Application::GetRenderer());
    
    m_vao->UnBind();
    TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Sent to buffer: vertices = {0}, indices = {1}", m_vertices.size(), m_indices.size());
}

void TESLA::Mesh::Draw(glm::vec3 cameraPosition)
{
    m_shader->Bind();
    UpdateMVPMatrix(cameraPosition);
    
    m_vao->Bind();
    TESLA::RenderCommand::Draw(m_vertices, m_indices);
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
    const uint32_t modelLocation = m_shader->GetUniformLocation("model");
    const uint32_t viewLocation = m_shader->GetUniformLocation("view");
    const uint32_t projectionLocation = m_shader->GetUniformLocation("projection");

    const uint32_t cameraLocation = m_shader->GetUniformLocation("cameraPosition");
    m_shader->UploadVector3(cameraLocation, cameraPosition);

    m_shader->UploadMatrix4(modelLocation, m_positionMatrix * m_rotationMatrix * m_scaleMatrix);
    m_shader->UploadMatrix4(viewLocation, m_viewMatrix);
    m_shader->UploadMatrix4(projectionLocation, m_projectionMatrix);
}






