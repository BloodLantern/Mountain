#pragma once

#include "draw.hpp"

namespace mountain
{
    struct Texture
    {
        unsigned int id;
        unsigned int width, height;
        unsigned char* data = nullptr;
        const char* path = nullptr;
        unsigned char channelCount; // The number of color channels in the texture (1-4).
        bool loaded = false;

        Texture() = default;
        Texture(const char* const filepath);
        ~Texture();

        void Load();
        void Load(const char* const filepath);
        void Unload();
    };
}
