#ifndef SKYBOX_H
#define SKYBOX_H

class SkyBox
{
private:
    unsigned int cubemapTexID;
    glm::vec3 ambientLight;
public:
    SkyBox(std::string skyboxName = "textures/skybox_default", glm::vec3 ambient = glm::vec3(0.2f))
    {
        ambientLight = ambient;
        std::vector<std::string> cubemapFaces;
        cubemapFaces.push_back(skyboxName +"/right.jpg");
        cubemapFaces.push_back(skyboxName +"/left.jpg");
        cubemapFaces.push_back(skyboxName +"/top.jpg");
        cubemapFaces.push_back(skyboxName +"/bottom.jpg");
        cubemapFaces.push_back(skyboxName +"/front.jpg");
        cubemapFaces.push_back(skyboxName +"/back.jpg");
        glGenTextures(1, &cubemapTexID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexID);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < cubemapFaces.size(); i++)
        {
            unsigned char *data = stbi_load(cubemapFaces[i].c_str(), &width, &height,
                                            &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                             width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap failed to load at path: " << cubemapFaces[i]
                          << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    unsigned int getID()
    {
        return cubemapTexID;
    }

    glm::vec3 getAmbientLight()
    {
        return ambientLight;
    }

    void setAmbientLight(glm::vec3 ambient)
    {
        ambientLight = ambient;
    }
};

#endif