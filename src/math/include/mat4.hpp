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

        Mat4(float* mat4)
        {
            _matrix = glm::make_mat4(mat4);
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

        void translate(float* translation_vector)
        {
            _matrix = glm::translate(_matrix, glm::make_vec3(translation_vector));
        }

        void rotate(float* rotation_vector, float degrees)
        {
            _matrix = glm::rotate(_matrix, glm::radians(degrees), glm::make_vec3(rotation_vector));
        }

        void scale(float* scaling_vector)
        {
            _matrix = glm::scale(_matrix, glm::make_vec3(scaling_vector));
        }

        void perspective(float viewportWidth, float viewportHeight)
        {
            _matrix = glm::perspective(glm::radians(45.0f), viewportWidth / viewportHeight, 0.1f, 100.0f);
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

} // namespace radiance::math::mat4
