#pragma once

#include <glad/glad.h>
#include "shader.hpp"
#include "texture.hpp"
#include "math.hpp"

namespace radiance::drawable
{
namespace rmath = radiance::math;
namespace rshader = radiance::shader;
namespace rtexture = radiance::texture;

class Drawable
{
public:
    virtual void bindContext() = 0;
    virtual void draw() = 0;

    virtual void setShader(rshader::Shader shader) {
        _shader = shader;
    }

    virtual void setTexture(rtexture::Texture texture) {};

    void translate(float* translation_vector )
    {
        _transformUpdate.translate( translation_vector );
    }

    void rotate(float* rotation_vector, float degrees)
    {
        _transformUpdate.rotate(rotation_vector, degrees);
    }

    void scale(float* scaling_vector)
    {
        _transformUpdate.scale(scaling_vector);
    }

    rshader::Shader _shader;
    rmath::Mat4 _transformUpdate;

protected:
    Drawable(float* vertices, uint32_t* indices, uint32_t vertices_size_bytes, uint32_t indices_size_bytes)
        : _vertices{ vertices }, _indices{ indices }, _vertices_size_bytes{ vertices_size_bytes }, _indices_size_bytes{ indices_size_bytes }
    {
        /******************** bind Vertex Array Object ********************************************/
        // generate a Vertex Attribute Object
        // Core OpenGL requires that we use a _VAO so it knows what to do with our vertex inputs.
        // If we fail to bind a _VAO, OpenGL will most likely refuse to draw anything.
        /*******************************************************************************************/
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        /************** copy our vertices array in a vertex buffer for OpenGL to use ***************/
        glGenBuffers(1, &_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices_size_bytes, vertices, GL_STATIC_DRAW);

        /*************** copy our index array in a element buffer for OpenGL to use ****************/
        glGenBuffers(1, &_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_size_bytes, indices, GL_STATIC_DRAW);
    }

    float* _vertices;
    uint32_t* _indices;
    uint32_t _vertices_size_bytes;
    uint32_t _indices_size_bytes;
    uint32_t _VAO;
    uint32_t _VBO;
    uint32_t _EBO;
};

class Drawable_F3POSF3COL : public Drawable
{
public:
    Drawable_F3POSF3COL(float* vertices, uint32_t* indices, uint32_t vertices_size_bytes, uint32_t indices_size_bytes)
        : Drawable( vertices, indices, vertices_size_bytes, indices_size_bytes)
    {

        /****************** set the vertex attributes pointers (vertex semantic) *******************/

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // unbind buffers, rebind explicitly when you want to draw this drawable
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Drawable_F3POSF3COL()
    {
        glDeleteVertexArrays(1, &_VAO);
        glDeleteBuffers(1, &_VBO);
        glDeleteBuffers(1, &_EBO);
    }

    void bindContext()
    {
        _shader.use();
        glBindVertexArray(_VAO);
    }

    void draw()
    {
        _shader.setTransform( _transformUpdate.getDataPtr() );
        glDrawElements(GL_TRIANGLES, _indices_size_bytes, GL_UNSIGNED_INT, 0);
        _transformUpdate = rmath::Mat4{};
    }

private:
};

class Drawable_F3POS : public Drawable
{
public:
    Drawable_F3POS(float* vertices, uint32_t* indices, uint32_t vertices_size_bytes, uint32_t indices_size_bytes)
        : Drawable(vertices, indices, vertices_size_bytes, indices_size_bytes)
    {

        /****************** set the vertex attributes pointers (vertex semantic) *******************/

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // unbind buffers, rebind explicitly when you want to draw this drawable
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Drawable_F3POS()
    {
        glDeleteVertexArrays(1, &_VAO);
        glDeleteBuffers(1, &_VBO);
        glDeleteBuffers(1, &_EBO);
    }

    void bindContext()
    {
        _shader.use();
        glBindVertexArray(_VAO);
    }

    void draw()
    {
        glDrawElements(GL_TRIANGLES, _indices_size_bytes, GL_UNSIGNED_INT, 0);
    }

private:
};

class Drawable_F3POSF2TEX : public Drawable
{
public:
    Drawable_F3POSF2TEX(float* vertices, uint32_t* indices, uint32_t vertices_size_bytes, uint32_t indices_size_bytes)
        : Drawable(vertices, indices, vertices_size_bytes, indices_size_bytes)
    {

        /****************** set the vertex attributes pointers (vertex semantic) *******************/
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coordinate attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // unbind buffers, rebind explicitly when you want to draw this drawable
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Drawable_F3POSF2TEX()
    {
        glDeleteVertexArrays(1, &_VAO);
        glDeleteBuffers(1, &_VBO);
        glDeleteBuffers(1, &_EBO);
    }

    void setTexture(rtexture::Texture texture) {
        _texture = texture;
    }

    void bindContext()
    {
        _shader.use();
        _texture.bind();
        glBindVertexArray(_VAO);
    }

    void draw()
    {
        glDrawElements(GL_TRIANGLES, _indices_size_bytes, GL_UNSIGNED_INT, 0);
    }

private:
    texture::Texture _texture;
};

}; // namespace radiance::drawable