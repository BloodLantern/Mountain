#include "texture.hpp"

#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <iostream>

mountain::Texture::Texture(const char *const filepath)
    : path(filepath)
{
}

mountain::Texture::~Texture()
{
    Unload();
}

void mountain::Texture::Load()
{
    if (path)
        Load(path);
    else
        std::cerr << "Texture file path is not set." << std::endl;
}

void mountain::Texture::Load(const char *const filepath)
{
    Unload();
    bool success = true;
    data = stbi_load(filepath, (int*) &width, (int*) &height, (int*) &channelCount, 4);

    if (data)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        GLenum channels = 0;
        if (channelCount == 3)
            channels = GL_RGB;
        else if (channelCount == 4)
            channels = GL_RGBA;
        else
        {
            std::cerr << "Unsupported number of channels: " << channelCount << std::endl;
            glDeleteTextures(1, &id);
            success = false;
        }

        if (success)
            glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, channels, GL_UNSIGNED_BYTE, data);
            
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
        success = false;

    if (success)
        loaded = true;
    else
    {
        std::cerr << "Texture failed to load at path: " << filepath << std::endl;
        success = false;
    }

    stbi_image_free(data);
}

void mountain::Texture::Unload()
{
    if (data)
    {
        glDeleteTextures(1, &id);
        loaded = false;
    }
}
