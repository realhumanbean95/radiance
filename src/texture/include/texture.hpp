#pragma once

#include <iostream>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace radiance::texture
{

    class Texture
    {
    public:
        
        Texture(const char* imagePath = R"(C:\Users\luket\repos\radiance\resources\texture\container.jpg)")
        {
            // create and bind the texture object
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // load and generate the texture
            int width, height, nrChannels;
            unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

            if (data)
            {
                stbi_set_flip_vertically_on_load(true);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }

            stbi_image_free(data);
        }

        void bind()
        {
            glBindTexture(GL_TEXTURE_2D, texture);
        }

    private:
        uint32_t texture;
    };

} // namespace radiance::texture
