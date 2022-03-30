#include <iostream>

#include "window.hpp"
#include "drawable.hpp"
#include "factory.hpp"
#include "shader.hpp"
#include "texture.hpp"

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

static void updateMvpMatrix( radiance::drawable::Drawable& drawable, const radiance::window::WindowGLFW& window )
{

    float rotation_vector2[]{ 1.0f, 0.0f, 0.0f };
    float translation_vector2[]{ 0.0f, 0.0f, -3.0f };

    // MVP transformations
    drawable.translateViewSpace(translation_vector2);
    drawable.rotateWorldSpace(rotation_vector2, -55.0f);
    drawable.perspectiveClipSpace(window._width, window._height);
}

int main(int argc, const char** argv)
{
    using namespace radiance;

    std::cout << "Hello Radiance!" << std::endl;

    window::WindowGLFW window{800, 600};

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

    auto drawable1 = factory.createDrawable(drawable::F3POSF3COL_INDEXED, vertices1, indices1, sizeof(vertices1), sizeof(indices1));
    drawable1->setShader(shader::Shader{});



    // verts for a quad
    float vertices2[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices2[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    auto drawable2 = factory.createDrawable(drawable::F3POSF2TEX, vertices2, sizeof(vertices2));

    shader::Shader shader{
        (radiance::cmake::project_dir + std::string(R"(\resources\shader\shader-texture.vs)") ).c_str(),
        (radiance::cmake::project_dir + std::string(R"(\resources\shader\shader-texture.fs)") ).c_str() 
    };

    drawable2->setShader(shader);

    drawable2->setTexture( texture::Texture{} );

    glEnable(GL_DEPTH_TEST);

    while ( !window.shouldClose() )
    {
        // input
        window.processInput();

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float translation_vector2[]{ 0.0f, 1.0f, -1.0f };
        float rotation_vector2[]{ 1.0f, 1.0f, 1.0f };

        drawable2->bindContext();
        updateMvpMatrix(*drawable2, window);
        drawable2->translateWorldSpace(translation_vector2);
        drawable2->rotateWorldSpace(rotation_vector2, (float)glfwGetTime() * 35);
        drawable2->draw(); // in OpenGL, render to back buffer

        float translation_vector[]{ 0.0f, 0.25f, 0.0f };
        float rotation_vector[]{ 0.0f, 1.0f, 0.0f };
        float scaling_vector[]{ 0.5, 0.5, 0.5 };

        drawable1->bindContext();

        updateMvpMatrix(*drawable1, window);

        drawable1->translateWorldSpace(translation_vector);
        drawable1->rotateWorldSpace(rotation_vector, (float)glfwGetTime() * 35);
        drawable1->scaleWorldSpace(scaling_vector);

        drawable1->draw(); // in OpenGL, render to back buffer

        // call events and swap front and back buffers
        window.swapBuffers();
        window.pollEvents();

        // 5 unbind vertex array
        glBindVertexArray(0);
    }

    return 0;
}
