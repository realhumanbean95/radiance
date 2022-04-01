#pragma once

#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace radiance::window
{

class WindowGLFW
{
public:
    WindowGLFW(int width, int height)
        : _width(width), _height(height)
    {
        /* Initialize the library */
        if (!glfwInit()) {
            std::cout << "glfwInit failed." << std::endl;
            //return -1;
        }


        // version information should eventually come from environment variables or some kind of external configuration
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(_width, _height, "Hello Radiance!", NULL, NULL);
        if (_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            //return -1;
        }
        glfwMakeContextCurrent(_window);
        
        // NOTE: framebufferSizeCallback is a static member function.
        glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            //return -1;
        }

        // NOTE: I think having this OpenGL call in this class makes the window abstraction leaky...
        // might eventually need to remove glad library as a dependency, only need glfw...
        glViewport(0, 0, _width, _height);

    }
    ~WindowGLFW()
    {
        glfwTerminate(); 
    }

    void processInput(
        std::function<void()> onWPress,
        std::function<void()> onSPress,
        std::function<void()> onAPress,
        std::function<void()> onDPress)
    {
        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(_window, true);
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            onWPress();
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            onSPress();
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
            onAPress();
        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
            onDPress();
    }

    void swapBuffers()
    {
        glfwSwapBuffers(_window);
    }

    void pollEvents()
    {
        glfwPollEvents();
    }

    bool shouldClose()
    {
        return glfwWindowShouldClose(_window);
    }

    float _width, _height;

private:
    // NOTE: made static so it could be passed to GLFW as a function pointer
    // May cause issues if we ever render multiple windows...not sure if they would share GLFW context etc...
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    GLFWwindow* _window;

};



}; // namespace radiance::window