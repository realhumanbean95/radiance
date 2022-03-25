#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"
#include "drawable.hpp"
#include "factory.hpp"
#include "shader.hpp"

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

int main(int argc, const char** argv)
{
    using namespace radiance;

    std::cout << "Hello Radiance!" << std::endl;

    window::WindowGLFW window{};

    // verts for a triangle
    float vertices1[] = {
        // positions       // colors
       -0.5f, -0.5f, 0.0f,  0.18f, 0.01f, 0.31f,   // bottom right
        0.5f, -0.5f, 0.0f,  0.97f, 0.67f, 0.32f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.96f, 0.18f, 0.59f    // top 
    };

    uint32_t indices1[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
    };

    drawable::DrawableFactory factory{};

    auto drawable1 = factory.createDrawable(drawable::F3POSF3COL, vertices1, indices1, sizeof(vertices1), sizeof(indices1));
    drawable1->setShader(shader::Shader{});

    // verts for a quad
    float vertices2[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices2[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    auto drawable2 = factory.createDrawable(drawable::F3POS, vertices2, indices2, sizeof(vertices2), sizeof(indices2));
    drawable2->setShader(shader::Shader{});


    while ( !window.shouldClose() )
    {
        // input
        window.processInput();

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawable2->bindContext();
        drawable2->draw(); // in OpenGL, render to back buffer

        drawable1->bindContext();
        drawable1->draw(); // // in OpenGL, render to back buffer

        //call events and swap buffers
        window.swapBuffers();
        window.pollEvents();

        // 5 unbind vertex array
        glBindVertexArray(0);
    }

    return 0;
}
