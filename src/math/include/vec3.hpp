#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace radiance::math::vec3
{
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

        const float* data()
        {
            return _data;
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

    static Vec3 cross(Vec3 vec1, Vec3 vec2)
    {
        glm::vec3 cross_product = glm::cross(
            glm::make_vec3( vec1.data() ),
            glm::make_vec3( vec2.data() ));
        
        return Vec3{ cross_product.x, cross_product.y, cross_product.z };
    }

} // namespace radiance::math::vec3