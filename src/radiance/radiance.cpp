#include <iostream>
#include <array>
#include <filesystem>

#include "data.hpp"

#include "window.hpp"
#include "drawable.hpp"
#include "factory.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "fly-camera.hpp"

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

namespace rcamera = radiance::camera;

int main(int argc, const char** argv)
{
    using namespace radiance;

    std::cout << "Hello Radiance!" << std::endl;

    window::WindowGLFW window{800, 600};
    if(window.windowCreationErrorCode != 0)
    {
        std::cout << window.errorMessage << std::endl;
        return window.windowCreationErrorCode;
    }

    drawable::DrawableFactory factory{};

    // instantiate and initialize first drawable
    auto triangle1 = factory.createDrawable(drawable::F3POSF3COL_INDEXED, vertices1, indices1, sizeof(vertices1), sizeof(indices1));
    triangle1->setShader(shader::Shader{});

    // instantiate and initialize second drawable
    auto box1 = factory.createDrawable(drawable::F3POSF2TEX, vertices2, sizeof(vertices2));
    box1->setShader(shader::Shader{
        (radiance::cmake::shader_dir/"shader-texture.vs").string().c_str(),
        (radiance::cmake::shader_dir/"shader-texture.fs").string().c_str()
    });
    box1->setTexture( texture::Texture{} );

    // instantiate and initialize second drawable
    auto lightSource1 = factory.createDrawable(drawable::F3POSF2TEX, vertices2, sizeof(vertices2));
    lightSource1->setShader(shader::Shader{
        (radiance::cmake::shader_dir/"shader-texture.vs").string().c_str(),
        (radiance::cmake::shader_dir/"shader-texture.fs").string().c_str()
    });
    lightSource1->setTexture( texture::Texture{
        (radiance::cmake::texture_dir/"sun.jpg").string().c_str()
    } );

    glEnable(GL_DEPTH_TEST);

    // camera
    radiance::camera::FlyCamera camera{};

    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    while ( !window.shouldClose() )
    {
        // per-frame time calculations
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        window.processInput(
            [&camera, &deltaTime](int direction) 
            { 
                camera.translate(
                    static_cast<rcamera::CameraMovement>(direction),
                    static_cast<float>(deltaTime));
            },
            [&camera](float xOffset, float yOffset)
            {
                camera.rotate(xOffset, yOffset);
            }
        );

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float rotation_vector2[]{ 1.0f, 1.0f, 1.0f };
        for (uint32_t i = 1; i < 10; i++)
        {
            box1->bindContext();
            box1->setViewMatrix(camera.getViewMatrix());
            box1->translate(objectPositions[i].data());
            box1->rotate(rotation_vector2, ((float)glfwGetTime() + 20.0f * i) * 25);
            box1->setProjectionMatrix(camera.getProjectionMatrix(window._width, window._height));
            box1->draw(); // in OpenGL, render to back buffer
        }
        
        float translation_vector[]{ 0.0f, 0.25f, 1.0f };
        float rotation_vector[]{ 0.0f, 1.0f, 0.0f };
        float scaling_vector[]{ 0.5, 0.5, 0.5 };
        for (uint32_t i = 1; i < 10; i++)
        {
            triangle1->bindContext();
            triangle1->setViewMatrix(camera.getViewMatrix());
            triangle1->translate(translation_vector);
            triangle1->translate(objectPositions[i].data());
            triangle1->rotate(rotation_vector, ((float)glfwGetTime() + 20.0f * i) * 25);
            triangle1->scale(scaling_vector);
            triangle1->setProjectionMatrix(camera.getProjectionMatrix(window._width, window._height));
            triangle1->draw(); // in OpenGL, render to back buffer
        }

        lightSource1->bindContext();
        lightSource1->setViewMatrix(camera.getViewMatrix());
        lightSource1->rotate(rotation_vector2, ((float)glfwGetTime()) * 12);
        lightSource1->scale(scaling_vector);
        lightSource1->setProjectionMatrix(camera.getProjectionMatrix(window._width, window._height));
        lightSource1->draw(); // in OpenGL, render to back buffer

        // call events and swap front and back buffers
        window.swapBuffers();
        window.pollEvents();

        // unbind vertex array
        glBindVertexArray(0);
    }

    return 0;
}
