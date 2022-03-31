#pragma once

#include <cstring>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

namespace radiance::math

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
    
    class Vec3
    {
    public:

        Vec3(float x, float y, float z)
        {
            _data[0] = x;
            _data[1] = y;
            _data[2] = z;
            _vector = glm::make_vec3(_data);
        }

        Vec3(const Vec3& vec) {
            memcpy(_data, glm::value_ptr(vec._vector), sizeof(float) * size());
            _vector = glm::make_vec3(_data);
        }

        Vec3 operator-(const Vec3& vec)
        {
            return Vec3{ _vector - vec._vector };
        }

        void normalize()
        {
            _vector = glm::normalize(_vector);
            _data[0] = _vector.x;
            _data[1] = _vector.y;
            _data[2] = _vector.z;
        }

        uint32_t size()
        {
            return _size;
        }

    private:
        float _data[3];
        glm::vec3 _vector;
        const uint32_t _size = 3;

        Vec3(glm::vec3 vec)
        {
            _vector = vec;
        }
    };

} // namespace radiance::math
