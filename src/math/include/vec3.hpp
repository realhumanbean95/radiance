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

        Vec3& operator+=(const Vec3& rhs)
        {
            this->_data[0] += rhs._data[0];
            this->_data[1] += rhs._data[1];
            this->_data[2] += rhs._data[2];
            this->_vector += rhs._vector;
            return *this;
        }

        Vec3& operator-=(const Vec3& rhs)
        {
            this->_data[0] -= rhs._data[0];
            this->_data[1] -= rhs._data[1];
            this->_data[2] -= rhs._data[2];
            this->_vector -= rhs._vector;
            return *this;
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

        const uint32_t _size = 3;
        float _data[3];

    private:
        
        glm::vec3 _vector;

        Vec3(glm::vec3 vec)
        {
            _data[0] = vec.x;
            _data[1] = vec.y;
            _data[2] = vec.z;
            _vector = vec;
        }
    };

    Vec3 operator-(const Vec3& vec1, const Vec3& vec2)
    {
        return Vec3{ 
            vec1._data[0] - vec2._data[0],
            vec1._data[1] - vec2._data[1],
            vec1._data[2] - vec2._data[2]
        };
    }

    Vec3 operator+(const Vec3& vec1, const Vec3& vec2)
    {
        return Vec3{
            vec1._data[0] + vec2._data[0],
            vec1._data[1] + vec2._data[1],
            vec1._data[2] + vec2._data[2]
        };
    }

    Vec3 operator*(const Vec3& vec, float scalar)
    {
        return Vec3{
            vec._data[0] * scalar,
            vec._data[1] * scalar,
            vec._data[2] * scalar
        };
    }

    Vec3 operator*(float scalar, const Vec3& vec)
    {
        return Vec3{
            vec._data[0] * scalar,
            vec._data[1] * scalar,
            vec._data[2] * scalar
        };
    }

    static Vec3 cross(Vec3 vec1, Vec3 vec2)
    {
        glm::vec3 cross_product = glm::cross(
            glm::make_vec3( vec1._data ),
            glm::make_vec3( vec2._data ));
        
        return Vec3{ cross_product.x, cross_product.y, cross_product.z };
    }

} // namespace radiance::math::vec3