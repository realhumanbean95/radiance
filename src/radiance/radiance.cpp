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

    glEnable(GL_DEPTH_TEST);

    drawable::DrawableFactory factory{};

    /**************************************************************************************************/
    //  Instantiate and initialize our drawables
    /**************************************************************************************************/
    // triangle1
    auto triangle1 = 
        factory.createDrawable(drawable::F3POSF3COL_INDEXED, vertices1, indices1, sizeof(vertices1), sizeof(indices1));
    triangle1->setShader(shader::Shader{
        (radiance::cmake::shader_dir / "unlit-color-attribute.vs").string().c_str() });

    // box1
    auto box1 = std::shared_ptr<drawable::Drawable>(
        factory.createDrawable(drawable::F3POSF2TEX, vertices2, sizeof(vertices2)));
    box1->setShader(shader::Shader{
        (radiance::cmake::shader_dir / "lit-texture.vs").string().c_str(),
        (radiance::cmake::shader_dir / "lit-texture.fs").string().c_str() });
    box1->setTexture( texture::Texture{} );

    // box2
    auto box2 = std::shared_ptr<drawable::Drawable>(
        factory.createDrawable(drawable::F3POSF2TEX, vertices2, sizeof(vertices2)));
    box2->setShader(shader::Shader{
        (radiance::cmake::shader_dir / "lit-texture.vs").string().c_str(),
        (radiance::cmake::shader_dir / "lit-texture.fs").string().c_str() });
    box2->setTexture(texture::Texture{
        (radiance::cmake::texture_dir / "wall.jpg").string().c_str() });

    // lightSource1
    auto lightSource1 = factory.createDrawable(drawable::F3POSF2TEX, vertices2, sizeof(vertices2));
    lightSource1->setShader(shader::Shader{
        (radiance::cmake::shader_dir/"unlit-texture.vs").string().c_str(),
        (radiance::cmake::shader_dir/"unlit-texture.fs").string().c_str() });
    lightSource1->setTexture( texture::Texture{
        (radiance::cmake::texture_dir/"sun.jpg").string().c_str() });

    /**************************************************************************************************/
    //  Put our lit drawable(s) into a list
    /**************************************************************************************************/
    std::list<std::shared_ptr<drawable::Drawable>> litObjects;
    litObjects.push_back( box1 );
    litObjects.push_back( box2 );

    // camera
    radiance::camera::FlyCamera camera{};

    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    while ( !window.shouldClose() )
    {

        /**************************************************************************************************/
        //  Handle KBaM input and update camera
        /**************************************************************************************************/
        // per-frame time calculations
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        window.processInput(
            // fly-camera keyboard control callback
            [&camera, &deltaTime](int direction) 
                { camera.translate( static_cast<rcamera::CameraMovement>(direction), static_cast<float>(deltaTime) ); },
            
            // fly-camera mouse control callback
            [&camera](float xOffset, float yOffset)
                { camera.rotate(xOffset, yOffset); }
        );

        /**************************************************************************************************/
        //  Apply lightColor to our lit objects
        /**************************************************************************************************/
        float lightColor[] = { 0.94f, 0.73f, 0.02f };
        std::ranges::for_each(litObjects, 
            [&lightColor](auto drawable) {
                drawable->bindContext();
                drawable->_shader.setVec3("lightColor", lightColor); 
        });

        /**************************************************************************************************/
        //  Apply transformations and render our objects
        /**************************************************************************************************/
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float rotation_vector2[]{ 1.0f, 1.0f, 1.0f };
        for (uint32_t i = 1; i < 5; i++)
        {
            box1->bindContext();
            box1->setViewMatrix(camera.getViewMatrix());
            box1->translate(objectPositions[i].data());
            box1->rotate(rotation_vector2, ((float)glfwGetTime() + 20.0f * i) * 25);
            box1->setProjectionMatrix(camera.getProjectionMatrix(window._width, window._height));
            box1->draw(); // in OpenGL, render to back buffer
        }

        for (uint32_t i = 5; i < 10; i++)
        {
            box2->bindContext();
            box2->setViewMatrix(camera.getViewMatrix());
            box2->translate(objectPositions[i].data());
            box2->rotate(rotation_vector2, ((float)glfwGetTime() + 20.0f * i) * 25);
            box2->setProjectionMatrix(camera.getProjectionMatrix(window._width, window._height));
            box2->draw(); // in OpenGL, render to back buffer
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
