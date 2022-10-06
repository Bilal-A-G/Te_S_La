#include "Mesh.h"
#ifdef PS_DEBUG
#include <iostream>
#endif


//Handles the creation of a vao, vbo, and ebo as well as loading the appropriate data to each
//Once done, assigns the mesh's vao
void Mesh::SetupGLObjects()
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void*>(sizeof(float) * 3));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

#ifdef PS_DEBUG
std::cout << "Sent to buffer: " << m_vertices.size() << " vertices, " << m_indices.size() << " indices \n";
#endif

    m_vao = vao;
}

void Mesh::Draw()
{
    UpdateMVPMatrix();
    
    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_vertices.size(), GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

//Wrapper functions around various glm transform functions. Just provides better syntax for now, but in the future will contain more functionality 

void Mesh::Rotate(float angle, glm::vec3 upVector)
{
    m_rotationMatrix = glm::rotate(IDENTITY_MAT, glm::radians(angle), upVector);
}

void Mesh::Scale(glm::vec3 scale)
{
    m_scaleMatrix = glm::scale(IDENTITY_MAT, scale);
}

void Mesh::Translate(glm::vec3 translation)
{
    m_positionMatrix = glm::translate(IDENTITY_MAT, translation);
}

//Updates the model view projection matrix uniform in the vertex shader TODO: move matrix multiplications into the vertex shader file, so it's done on the GPU instead of the CPU
void Mesh::UpdateMVPMatrix()
{
    const GLint mvp_location = glGetUniformLocation(m_shaderProgram, "MVP");
    glm::mat4 mvpMatrix = m_projectionMatrix * m_viewMatrix * (m_positionMatrix * m_rotationMatrix * m_scaleMatrix);
    
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvpMatrix[0][0]);
}





