#include <iostream>
#include <array>

#include "data.hpp"

#include "window.hpp"
#include "drawable.hpp"
#include "factory.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vec3.hpp"

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

namespace rvec3 = radiance::math::vec3;

static void updateCamera(radiance::drawable::Drawable& drawable, const radiance::window::WindowGLFW& window)
{
    rvec3::Vec3 camera_pos{ 0.0f, 0.0f, 8.0f };
    rvec3::Vec3 camera_target{ 0.0f, 0.0f, 0.0f };
    rvec3::Vec3 camera_dir = rvec3::Vec3(camera_pos - camera_target);
    camera_dir.normalize();

    rvec3::Vec3 up{ 0.0f, 1.0f, 0.0f };
    rvec3::Vec3 camera_right = rvec3::cross(up, camera_dir);
    camera_right.normalize();

    rvec3::Vec3 camera_up = rvec3::cross(camera_dir, camera_right);

    float translation_vector2[]{ 0.0f, 0.0f, -8.0f };

    // MVP transformations
    drawable.translateViewSpace(translation_vector2);
}

int main(int argc, const char** argv)
{
    using namespace radiance;

    std::cout << "Hello Radiance!" << std::endl;

    window::WindowGLFW window{800, 600};

    drawable::DrawableFactory factory{};

    // instantiate and initialize first drawable
    auto drawable1 = factory.createDrawable(drawable::F3POSF3COL_INDEXED, vertices1, indices1, sizeof(vertices1), sizeof(indices1));
    drawable1->setShader(shader::Shader{});

    // instantiate and initialize second drawable
    auto drawable2 = factory.createDrawable(drawable::F3POSF2TEX, vertices2, sizeof(vertices2));
    drawable2->setShader(shader::Shader{
        (radiance::cmake::project_dir + std::string(R"(\resources\shader\shader-texture.vs)")).c_str(),
        (radiance::cmake::project_dir + std::string(R"(\resources\shader\shader-texture.fs)")).c_str()
    });
    drawable2->setTexture( texture::Texture{} );

    glEnable(GL_DEPTH_TEST);

    while ( !window.shouldClose() )
    {
        // input
        window.processInput();

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float rotation_vector2[]{ 1.0f, 1.0f, 1.0f };
        for (uint32_t i = 0; i < 10; i++)
        {
            drawable2->bindContext();
            updateCamera(*drawable2, window);
            drawable2->translateWorldSpace(objectPositions[i].data());
            float angle = 20.0f * i;
            drawable2->rotateWorldSpace(rotation_vector2, ((float)glfwGetTime() + angle) * 25);
            drawable2->perspectiveClipSpace(window._width, window._height);
            drawable2->draw(); // in OpenGL, render to back buffer
        }
        
        float translation_vector[]{ 0.0f, 0.25f, 1.0f };
        float rotation_vector[]{ 0.0f, 1.0f, 0.0f };
        float scaling_vector[]{ 0.5, 0.5, 0.5 };
        for (uint32_t i = 0; i < 10; i++)
        {
            drawable1->bindContext();
            updateCamera(*drawable1, window);
            drawable1->translateWorldSpace(translation_vector);
            drawable1->translateWorldSpace(objectPositions[i].data());
            float angle = 20.0f * i;
            drawable1->rotateWorldSpace(rotation_vector, ((float)glfwGetTime() + angle) * 25);
            drawable1->scaleWorldSpace(scaling_vector);
            drawable1->perspectiveClipSpace(window._width, window._height);
            drawable1->draw(); // in OpenGL, render to back buffer
        }

        // call events and swap front and back buffers
        window.swapBuffers();
        window.pollEvents();

        // 5 unbind vertex array
        glBindVertexArray(0);
    }

    return 0;
}
