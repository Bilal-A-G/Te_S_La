#pragma once
#include <array>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct vertex
{
    glm::vec3 position{};
    glm::vec2 uv{};
    glm::vec3 normal{};
};

class mesh_loader
{
public:
    void get_mesh_vertices(const char* file_name, std::vector<vertex>& vertices);
    void get_mesh_indices(const char* file_name, std::vector<uint16_t>& indices);
};
