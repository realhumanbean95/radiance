#pragma once

#include "mat4.hpp"
#include "vec3.hpp"

namespace radiance::camera
{
namespace rmat4 = radiance::math::mat4;
namespace rvec3 = radiance::math::vec3;

enum CameraMovement {
    FORWARD = 0,
    BACKWARD = 1,
    LEFT = 2,
    RIGHT = 3
};

class FlyCamera
{
public:

    FlyCamera()
    {
        _yaw = 90.0f;
        _pitch = 0.0f;
        _movementSpeed = 2.5;
        _mouseSensitivity = 0.1f;
    }

    rmat4::Mat4 getViewMatrix()
    {
        return rmat4::lookAt(_cameraPos._data, (_cameraPos + _cameraFront)._data, _cameraUp._data);
    }

    void translate(CameraMovement direction, float deltaTime)
    {
        float velocity = _movementSpeed * deltaTime;
        if (direction == FORWARD)
            moveForward(velocity);
        if (direction == BACKWARD)
            moveBackward(velocity);
        if (direction == LEFT)
            moveLeft(velocity);
        if (direction == RIGHT)
            moveRight(velocity);
    }

    void rotate(float xOffset, float yOffset)
    {
        _yaw += xOffset * _mouseSensitivity;
        _pitch += yOffset * _mouseSensitivity;

        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;

        float x = -cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        float y = sin(glm::radians(_pitch));
        float z = -sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

        _cameraFront = rvec3::Vec3{ x, y, z };
        _cameraFront.normalize();
    }

    rvec3::Vec3 _cameraPos{ 0.0f, 0.0f, 3.0f };
    rvec3::Vec3 _cameraFront{ 0.0f, 0.0f, -1.0 };
    rvec3::Vec3 _cameraUp{ 0.0f, 1.0f, 0.0f };

    float _pitch, _yaw;
    float _movementSpeed;
    float _mouseSensitivity;

private:
    void moveForward(float movementSpeed)
    {
        _cameraPos += movementSpeed * _cameraFront;
    }

    void moveBackward(float movementSpeed)
    {
        _cameraPos -= movementSpeed * _cameraFront;
    }

    void moveLeft(float movementSpeed)
    {
        rvec3::Vec3 tmp = rvec3::cross(_cameraFront, _cameraUp);
        tmp.normalize();
        _cameraPos -= tmp * movementSpeed;
    }

    void moveRight(float movementSpeed)
    {
        rvec3::Vec3 tmp = rvec3::cross(_cameraFront, _cameraUp);
        tmp.normalize();
        _cameraPos += tmp * movementSpeed;
    }

};

} // namespace radiance::camera