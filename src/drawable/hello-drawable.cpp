#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "drawable.hpp"
#include "shader.hpp"

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, const char** argv)
{
    std::cout << "Hello Drawable!" << std::endl;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit failed." << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle!", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    Shader shader1(
        R"(C:\Users\luket\repos\radiance\resources\shader\shader1.vs)",
        R"(C:\Users\luket\repos\radiance\resources\shader\shader1.fs)"
    );

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

    auto drawable1 = Drawable(vertices1, indices1, sizeof(vertices1), sizeof(indices1));

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

    auto drawable2 = Drawable(vertices2, indices2, sizeof(vertices2), sizeof(indices2));


    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader1.use();

        drawable1.bindVAO();
        drawable1.draw();

        //drawable2.bindVAO();
        //drawable2.draw();

        //call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // 5 unbind vertex array
        glBindVertexArray(0);
    }

    glfwTerminate();
    return 0;
}
