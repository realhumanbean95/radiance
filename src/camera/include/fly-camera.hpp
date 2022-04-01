#pragma once

#include "mat4.hpp"
#include "vec3.hpp"

namespace radiance::camera
{
namespace rmat4 = radiance::math::mat4;
namespace rvec3 = radiance::math::vec3;

class FlyCamera
{
public:

    FlyCamera()
    {
        _viewMatrix = rmat4::lookAt(cameraPos._data, (cameraPos + cameraFront)._data, cameraUp._data);
    }

    void moveForward(float cameraSpeed)
    {
        cameraPos += cameraSpeed * cameraFront;
        _viewMatrix = rmat4::lookAt(cameraPos._data, (cameraPos + cameraFront)._data, cameraUp._data);
    }

    void moveBackward(float cameraSpeed)
    {
        cameraPos -= cameraSpeed * cameraFront;
        _viewMatrix = rmat4::lookAt(cameraPos._data, (cameraPos + cameraFront)._data, cameraUp._data);
    }

    void moveLeft(float cameraSpeed)
    {
        rvec3::Vec3 tmp = rvec3::cross(cameraFront, cameraUp);
        tmp.normalize();
        cameraPos -= tmp * cameraSpeed;
        _viewMatrix = rmat4::lookAt(cameraPos._data, (cameraPos + cameraFront)._data, cameraUp._data);
    }

    void moveRight(float cameraSpeed)
    {
        rvec3::Vec3 tmp = rvec3::cross(cameraFront, cameraUp);
        tmp.normalize();
        cameraPos += tmp * cameraSpeed;
        _viewMatrix = rmat4::lookAt(cameraPos._data, (cameraPos + cameraFront)._data, cameraUp._data);
    }

    rvec3::Vec3 cameraPos{ 0.0f, 0.0f, 3.0f };
    rvec3::Vec3 cameraFront{ 0.0f, 0.0f, -1.0 };
    rvec3::Vec3 cameraUp{ 0.0f, 1.0f, 0.0f };

    rmat4::Mat4 _viewMatrix;
};

} // namespace radiance::camera