#pragma once

#include <iostream>

#include <glad/glad.h>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace radiance::texture
{

    class Texture
    {
    public:
        // should consider refactor to load texture into memory on construction, defer sending to GPU...maybe.
        Texture(const char* imagePath = (radiance::cmake::texture_dir + std::string(R"(container.jpg)")).c_str()  )
        {
            // create and bind the texture object
            glGenTextures(1, &_texture);
            glBindTexture(GL_TEXTURE_2D, _texture);

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
            glBindTexture(GL_TEXTURE_2D, _texture);
        }

    private:
        uint32_t _texture;
    };

} // namespace radiance::texture
