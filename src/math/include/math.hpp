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
        glm::mat4 trans;

        Mat4(float* mat4)
        {
            trans = glm::make_mat4(mat4);
        }

        Mat4()
        {
            trans = glm::mat4(1.0f);
        }

        Mat4 operator*( const Mat4& Mat4_0 )
        {
            glm::mat4 result = trans * Mat4_0.trans;
            return Mat4{ glm::value_ptr(result) };
        }

        void translate(float* translation_vector)
        {
            trans = glm::translate(trans, glm::make_vec3(translation_vector));
        }

        void rotate(float* rotation_vector, float degrees)
        {
            trans = glm::rotate(trans, degrees, glm::make_vec3(rotation_vector));
        }

        void scale(float* scaling_vector)
        {
            trans = glm::scale(trans, glm::make_vec3(scaling_vector));
        }

        float* getDataPtr()
        {
            return glm::value_ptr(trans);
        }

    private:

        Mat4(glm::mat4 _mat4) : trans( _mat4 )
        {}
    };

} // namespace radiance::math
