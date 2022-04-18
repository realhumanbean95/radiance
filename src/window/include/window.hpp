#pragma once

#include <functional>
#include <cstring>

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

        // initialize x/y values to middle of window
        _lastXPos = _width / 2;
        _lastYPos = _height / 2;
        _xOffset = 0.0f;
        _yOffset = 0.0f;

        // version information should eventually come from environment variables or some kind of external configuration
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(_width, _height, "Hello Radiance!", NULL, NULL);
        if (_window == NULL)
        {
            std::memcpy(errorMessage, "Failed to initialize GLAD", 25);
            windowCreationErrorCode = -1;
            glfwTerminate();
            return;
        }
        
        glfwMakeContextCurrent(_window);
        
        // NOTE: framebufferSizeCallback is a static member function.
        glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::strncpy(errorMessage, "Failed to initialize GLAD", 25);
            windowCreationErrorCode = -1;
            return;
        }

        // NOTE: I think having this OpenGL call in this class makes the window abstraction leaky...
        // might eventually need to remove glad library as a dependency, only need glfw...
        glViewport(0, 0, _width, _height);

        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }
    ~WindowGLFW()
    {
        glfwTerminate(); 
    }

    void processInput(
        std::function<void(int)> cameraKeyboardCallback,
        std::function<void(float, float)> cameraMouseCallback)
    {
        bool leftAltKeyPressed = false; // when true, means waiting for GLFW_RELEASE for GLFW_KEY_LEFT_ALT
        bool mouse3Pressed = false; // when true, means waiting for GLFW_RELEASE for GLFW_MOUSE_BUTTON_3

        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(_window, true);
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            cameraKeyboardCallback(0);
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            cameraKeyboardCallback(1);
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
            cameraKeyboardCallback(2);
        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
            cameraKeyboardCallback(3);
        if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS && !leftAltKeyPressed)
        {
            mouse3Pressed = true;
            glfwGetCursorPos(_window, &_xPos, &_yPos);
            if(first_mouse)
            { 
                _lastXPos = _xPos;
                _lastYPos = _yPos;
                first_mouse = false;
            }

            _xOffset = _xPos - _lastXPos;
            _yOffset = _lastYPos - _yPos;

            _lastXPos = _xPos;
            _lastYPos = _yPos;

            cameraMouseCallback(_xOffset, _yOffset);
        }
        if ( (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_3) == GLFW_RELEASE && !first_mouse) && mouse3Pressed )
        {
            first_mouse = true;
            mouse3Pressed = false;
        }
        if (glfwGetKey(_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && !mouse3Pressed)
        {
            leftAltKeyPressed = true;
            glfwGetCursorPos(_window, &_xPos, &_yPos);
            if (first_mouse)
            {
                _lastXPos = _xPos;
                _lastYPos = _yPos;
                first_mouse = false;
            }

            _xOffset = _xPos - _lastXPos;
            _yOffset = _lastYPos - _yPos;

            _lastXPos = _xPos;
            _lastYPos = _yPos;

            cameraMouseCallback(_xOffset, _yOffset);
        }
        if (glfwGetKey(_window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE && !first_mouse && leftAltKeyPressed)
        {
            first_mouse = true;
            leftAltKeyPressed = false;

        }
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
    double _xPos, _yPos;
    double _lastXPos, _lastYPos;
    double _xOffset, _yOffset;
    bool first_mouse = true;

    int windowCreationErrorCode = 0;
    char errorMessage[100];


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