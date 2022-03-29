#pragma once

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
            _trans = glm::make_mat4(mat4);
        }

        Mat4()
        {
            _trans = glm::mat4(1.0f);
        }

        Mat4 operator*( const Mat4& mat4 )
        {
            glm::mat4 result = _trans * mat4._trans;
            return Mat4{ glm::value_ptr(result) };
        }

        void translate(float* translation_vector)
        {
            _trans = glm::translate(_trans, glm::make_vec3(translation_vector));
        }

        void rotate(float* rotation_vector, float degrees)
        {
            _trans = glm::rotate(_trans, degrees, glm::make_vec3(rotation_vector));
        }

        void scale(float* scaling_vector)
        {
            _trans = glm::scale(_trans, glm::make_vec3(scaling_vector));
        }

        float* getDataPtr()
        {
            return glm::value_ptr(_trans);
        }

    private:
        glm::mat4 _trans;

        Mat4(glm::mat4 mat4) : _trans( mat4 )
        {}
    };

} // namespace radiance::math
