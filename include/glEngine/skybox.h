#ifndef SKYBOX_H
#define SKYBOX_H

class SkyBox
{
private:
    unsigned int cubemapTexID;
public:
    SkyBox()
    {
        std::vector<std::string> cubemapFaces;
        cubemapFaces.push_back("textures/skybox/right.jpg");
        cubemapFaces.push_back("textures/skybox/left.jpg");
        cubemapFaces.push_back("textures/skybox/top.jpg");
        cubemapFaces.push_back("textures/skybox/bottom.jpg");
        cubemapFaces.push_back("textures/skybox/front.jpg");
        cubemapFaces.push_back("textures/skybox/back.jpg");
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
};

#endif