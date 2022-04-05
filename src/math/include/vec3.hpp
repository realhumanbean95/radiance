#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace radiance::math::vec3
{
    class Vec3
    {
    public:

        Vec3()
        {
            _data[0] = 0.0f;
            _data[1] = 0.0f;
            _data[2] = 0.0f;
            
        }

        Vec3(float x, float y, float z)
        {
            _data[0] = x;
            _data[1] = y;
            _data[2] = z;
        }

        Vec3(const Vec3& vec) {
            memcpy( _data, vec._data, _sizeInBytes );
        }

        Vec3& operator+=(const Vec3& rhs)
        {
            this->_data[0] += rhs._data[0];
            this->_data[1] += rhs._data[1];
            this->_data[2] += rhs._data[2];
            return *this;
        }

        Vec3& operator-=(const Vec3& rhs)
        {
            this->_data[0] -= rhs._data[0];
            this->_data[1] -= rhs._data[1];
            this->_data[2] -= rhs._data[2];
            return *this;
        }

        void operator=(const Vec3& rhs)
        {
            this->_data[0] = rhs._data[0];
            this->_data[1] = rhs._data[1];
            this->_data[2] = rhs._data[2];
        }

        const static uint32_t _size = 3;
        const static uint32_t _sizeInBytes = _size * sizeof(float);
        float _data[_size];

    private:
        

        Vec3(glm::vec3 vec)
        {
            _data[0] = vec.x;
            _data[1] = vec.y;
            _data[2] = vec.z;
        }
    };

    std::ostream& operator<<(std::ostream& lhs, const Vec3& rhs)
    {
        lhs << "{ " << rhs._data[0] << ", " << rhs._data[1] << ", " << rhs._data[2] << " }";
        return lhs;
    }

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

    static Vec3 normalize(const Vec3& vector)
    {
        glm::vec3 normalized_vector = glm::normalize(glm::make_vec3(vector._data));
        return Vec3{ normalized_vector.x, normalized_vector.y, normalized_vector.z };
    }

} // namespace radiance::math::vec3