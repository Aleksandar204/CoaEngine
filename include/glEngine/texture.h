#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Texture
{
private:
    unsigned int texture_id;

public:
    std::string type;
    Texture(const char *texturePath)
    {
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

        GLenum format;
        switch (nrChannels)
        {
        // case 1:
        //     format = GL_LUMINANCE;
        //     break;
        // case 2:
        //     format = GL_LUMINANCE_ALPHA;
        //     break;
        case 3:
            format = GL_RGB;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case 4:
            format = GL_RGBA;
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Transparent texture edges have artifacts around the edges when repeating, this should be GL_CLAMP but it messes up other things TODO: find solution
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        }

        if (data)
        {
            // std::cout << nrChannels << std::endl;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            throw new std::runtime_error("Failed to load texture");
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    ~Texture()
    {
        glDeleteTextures(1,&texture_id);
    }

    void use()
    {
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }
    unsigned int get_id()
    {
        return texture_id;
    }
};
#endif