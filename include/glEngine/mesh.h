#ifndef MESH_H
#define MESH_H

#include <glEngine/texture.h>
#include <glEngine/shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

class Mesh
{
private:
    unsigned int VAO,VBO,EBO;
public:
    Shader shader;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> diffuseMaps;
    std::vector<Texture*> specularMaps;
    std::vector<Texture*> normalMaps;
    std::vector<Texture*> heightMaps;

    Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture*> diffuse, std::vector<Texture*> specular, std::vector<Texture*> normalmap, std::vector<Texture*> height)
    {
        vertices = vert;
        indices = ind;
        diffuseMaps = diffuse;
        specularMaps = specular;
        heightMaps = height;
        normalMaps = normalmap;

        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);
        glGenBuffers(1,&EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
    unsigned int getVAO()
    {
        return VAO;
    }
};

#endif