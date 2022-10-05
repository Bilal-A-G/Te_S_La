#include "mesh_loader.h"
#include <fstream>
#include <iostream>

const std::string MODELS_DIR = "./res/";

//TODO: Refactor out duplicate code using templates
void mesh_loader::get_mesh_vertices(const char* file_name, std::vector<vertex>& vertices)
{
    std::ifstream vbo_file;
    
    vbo_file.open(MODELS_DIR + file_name, std::ios::in | std::ios::binary);
    if(!vbo_file.is_open())
    {
        std::cout << "Failed to open file " << MODELS_DIR + file_name;
    }
    
    int num_vertices = 0;
    vbo_file.read(reinterpret_cast<char*>(&num_vertices), sizeof(int));

    vertices.resize(num_vertices);
    vbo_file.read(reinterpret_cast<char*>(vertices.data()), sizeof(vertex) * num_vertices);
}

void mesh_loader::get_mesh_indices(const char* file_name, std::vector<uint16_t>& indices)
{
    std::ifstream vboFile(MODELS_DIR + file_name, std::ifstream::in | std::ifstream::binary);

    int num_indices = 0;
    vboFile.read(reinterpret_cast<char*>(&num_indices), sizeof(int));

    indices.resize(num_indices);
    vboFile.read(reinterpret_cast<char*>(indices.data()), sizeof(uint16_t) * num_indices);
}

