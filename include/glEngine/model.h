#ifndef MODEL_H
#define MODEL_H

#include <glEngine/shader.h>
#include <glEngine/mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(std::string modelPath)
    {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs | aiProcess_PreTransformVertices);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "ERRR" << std::endl;
            throw new std::runtime_error(importer.GetErrorString());
        }
        directory = modelPath.substr(0, modelPath.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void processNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh,scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh processMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture*> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vec;
            vec.x = mesh->mVertices[i].x;
            vec.y = mesh->mVertices[i].y;
            vec.z = mesh->mVertices[i].z;
            vertex.position = vec;

            vec.x = mesh->mVertices[i].x;
            vec.y = mesh->mVertices[i].y;
            vec.z = mesh->mVertices[i].z;
            vertex.normal = vec;

            if(mesh->mTextureCoords[0])
            {
                glm::vec2 v;
                v.x = mesh->mTextureCoords[0][i].x;
                v.y = mesh->mTextureCoords[0][i].y;
                vertex.tex_coords = v;
            }
            else
                vertex.tex_coords = glm::vec2(0.0f,0.0f);

            vertices.push_back(vertex);
        }
        for (unsigned int  i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }
        
        return Mesh(vertices, indices, textures);
    }

    Model(std::string modelPath)
    {
        loadModel(modelPath);
    }
    ~Model()
    {

    }
};

#endif