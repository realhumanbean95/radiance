#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

namespace radiance::math::mat4

{   
    class Mat4
    {
    public:

        Mat4(const float mat4[16])
        {
            _matrix = glm::make_mat4(mat4);
        }

        Mat4(const Mat4& matrix)
        {
            _matrix = matrix._matrix;
        }

        Mat4()
        {
            _matrix = glm::mat4(1.0f);
        }

        Mat4 operator*( const Mat4& mat4 )
        {
            glm::mat4 result = _matrix * mat4._matrix;
            return Mat4{ glm::value_ptr(result) };
        }

        void translate(const float translation_vector[3])
        {
            _matrix = glm::translate(_matrix, glm::make_vec3(translation_vector));
        }

        void rotate(const float rotation_vector[3], float degrees)
        {
            _matrix = glm::rotate(_matrix, glm::radians(degrees), glm::make_vec3(rotation_vector));
        }

        void scale(const float scaling_vector[3])
        {
            _matrix = glm::scale(_matrix, glm::make_vec3(scaling_vector));
        }

        float* getDataPtr()
        {
            return glm::value_ptr(_matrix);
        }

    private:
        glm::mat4 _matrix;

        Mat4(glm::mat4 mat4) : _matrix( mat4 )
        {}
    };

    Mat4 lookAt(float eye[3], float center[3], float up[3])
    {
        return Mat4{ glm::value_ptr(glm::lookAt(glm::make_vec3(eye), glm::make_vec3(center), glm::make_vec3(up))) };
    }

    Mat4 perspective(float viewportWidth, float viewportHeight, float fov = 45.0f, float near = 0.1f, float far = 0.1f)
    {
        return Mat4{ glm::value_ptr(glm::perspective(glm::radians(fov), viewportWidth / viewportHeight, 0.1f, 100.0f)) };
    }

} // namespace radiance::math::mat4
