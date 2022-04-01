#pragma once

#include <glad/glad.h>
#include "shader.hpp"
#include "texture.hpp"
#include "mat4.hpp"

namespace radiance::drawable
{
namespace rmat4 = radiance::math::mat4;
namespace rshader = radiance::shader;
namespace rtexture = radiance::texture;

class Drawable
{
public:
    virtual void bindContext() = 0;

    virtual void draw()
    {
        _shader.setModelMatrix(_modelMatrix.getDataPtr());
        _shader.setViewMatrix(_viewMatrix.getDataPtr());
        _shader.setProjectionMatrix(_projectionMatrix.getDataPtr());

        glDrawArrays(GL_TRIANGLES, 0, _vertices_size_bytes);
        _modelMatrix = rmat4::Mat4{};
        _viewMatrix = rmat4::Mat4{};
        _projectionMatrix = rmat4::Mat4{};

    }

    virtual void setShader(rshader::Shader shader) {
        _shader = shader;
    }

    virtual void setTexture(rtexture::Texture texture) {};

    void translateWorldSpace(float* translation_vector )
    {
        _modelMatrix.translate( translation_vector );
    }

    void rotateWorldSpace(float* rotation_vector, float degrees)
    {
        _modelMatrix.rotate(rotation_vector, degrees);
    }

    void scaleWorldSpace(float* scaling_vector)
    {
        _modelMatrix.scale(scaling_vector);
    }

    void translateViewSpace(float* translation_vector)
    {
        _viewMatrix.translate(translation_vector);
    }

    void rotateViewSpace(float* rotation_vector, float degrees)
    {
        _viewMatrix.rotate(rotation_vector, degrees);
    }

    void scaleViewSpace(float* scaling_vector)
    {
        _viewMatrix.scale(scaling_vector);
    }

    void perspectiveClipSpace(float viewportWidth, float viewportHeight)
    {
        _projectionMatrix.perspective(viewportWidth, viewportHeight);
    }

    void setViewMatrix(const glm::mat4& matrix)
    {
        _viewMatrix = rmat4::Mat4{ glm::value_ptr(matrix) };
    }

protected:
    Drawable(float* vertices, uint32_t vertices_size_bytes)
        : _vertices{ vertices }, _vertices_size_bytes{ vertices_size_bytes }
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

    }

    float* _vertices;
    uint32_t _vertices_size_bytes;
    uint32_t _VAO;
    uint32_t _VBO;

    rshader::Shader _shader;
    rmat4::Mat4 _modelMatrix;
    rmat4::Mat4 _viewMatrix;
    rmat4::Mat4 _projectionMatrix;

};

class DrawableIndexed : public Drawable
{

protected:
    uint32_t* _indices;
    uint32_t _indices_size_bytes;
    uint32_t _EBO;

    DrawableIndexed(float* vertices, uint32_t* indices, uint32_t vertices_size_bytes, uint32_t indices_size_bytes)
        : Drawable(vertices, vertices_size_bytes), _indices(indices), _indices_size_bytes(indices_size_bytes)
    {
        /*************** copy our index array in a element buffer for OpenGL to use ****************/
        glGenBuffers(1, &_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_size_bytes, indices, GL_STATIC_DRAW);
    }

public:
    virtual void draw()
    {
        _shader.setModelMatrix(_modelMatrix.getDataPtr());
        _shader.setViewMatrix(_viewMatrix.getDataPtr());
        _shader.setProjectionMatrix(_projectionMatrix.getDataPtr());

        glDrawElements(GL_TRIANGLES, _indices_size_bytes, GL_UNSIGNED_INT, 0);
        _modelMatrix = rmat4::Mat4{};
        _viewMatrix = rmat4::Mat4{};
        _projectionMatrix = rmat4::Mat4{};
    }

};

class Drawable_F3POSF3COL_Indexed : public DrawableIndexed
{
public:
    Drawable_F3POSF3COL_Indexed(float* vertices, uint32_t* indices, uint32_t vertices_size_bytes, uint32_t indices_size_bytes)
        : DrawableIndexed( vertices, indices, vertices_size_bytes, indices_size_bytes)
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

    ~Drawable_F3POSF3COL_Indexed()
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

private:
};

class Drawable_F3POS_Indexed : public DrawableIndexed
{
public:
    Drawable_F3POS_Indexed(float* vertices, uint32_t* indices, uint32_t vertices_size_bytes, uint32_t indices_size_bytes)
        : DrawableIndexed(vertices, indices, vertices_size_bytes, indices_size_bytes)
    {

        /****************** set the vertex attributes pointers (vertex semantic) *******************/

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // unbind buffers, rebind explicitly when you want to draw this drawable
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Drawable_F3POS_Indexed()
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

private:
};

class Drawable_F3POSF2TEX_Indexed : public DrawableIndexed
{
public:
    Drawable_F3POSF2TEX_Indexed(float* vertices, uint32_t* indices, uint32_t vertices_size_bytes, uint32_t indices_size_bytes)
        : DrawableIndexed(vertices, indices, vertices_size_bytes, indices_size_bytes)
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

    ~Drawable_F3POSF2TEX_Indexed()
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

private:
    texture::Texture _texture;
};

class Drawable_F3POSF2TEX : public Drawable
{
public:
    Drawable_F3POSF2TEX(float* vertices, uint32_t vertices_size_bytes)
        : Drawable(vertices, vertices_size_bytes)
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

private:
    texture::Texture _texture;
};

}; // namespace radiance::drawable