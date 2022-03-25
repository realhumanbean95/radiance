#include <iostream>

#include "window.hpp"
#include "drawable.hpp"
#include "factory.hpp"
#include "shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

int main(int argc, const char** argv)
{
    using namespace radiance;

    std::cout << "Hello Radiance!" << std::endl;

    window::WindowGLFW window{800, 600};

    // verts for a quad
    float vertices2[] = {
        // positions        // colors
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f,  0.0f, 1.0f   // top left 
    };

    unsigned int indices2[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // create and bind the texture object
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(R"(C:\Users\luket\repos\radiance\resources\texture\container.jpg)", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    shader::Shader shader{
        R"(C:\Users\luket\repos\radiance\resources\shader\shader-texture.vs)",
        R"(C:\Users\luket\repos\radiance\resources\shader\shader-texture.fs)" };
    //shader.setInt("ourTexture", texture);
    
    drawable::DrawableFactory factory{};

    auto drawable2 = factory.createDrawable(drawable::F3POSF2TEX, vertices2, indices2, sizeof(vertices2), sizeof(indices2));
    drawable2->setShader(
        shader
    );

    while ( !window.shouldClose() )
    {
        // input
        window.processInput();

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glBindTexture(GL_TEXTURE_2D, texture);
        drawable2->bindContext();
        drawable2->draw(); // in OpenGL, render to back buffer

        //call events and swap buffers
        window.swapBuffers();
        window.pollEvents();

    }

    return 0;
}
