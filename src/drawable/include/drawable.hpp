#pragma once
#include <glad/glad.h>
#include "shader.hpp"

namespace radiance::drawable
{

class Drawable
{
public:
    virtual void bindContext() = 0;
    virtual void draw() = 0;

    virtual void setShader(radiance::shader::Shader _shader) {
        shader = _shader;
    }

    radiance::shader::Shader shader;
};

class Drawable_F3POSF3COL : public Drawable
{
public:
    Drawable_F3POSF3COL(float* _vertices, uint32_t* _indices, uint32_t _vertices_size_bytes, uint32_t _indices_size_bytes)
        : vertices{ _vertices }, indices{ _indices }, vertices_size_bytes{ _vertices_size_bytes }, indices_size_bytes{ _indices_size_bytes }
    {
        // 1. bind Vertex Array Object
        // generate a Vertex Attribute Object
        // Core OpenGL requires that we use a VAO so it knows what to do with our vertex inputs.
        // If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // 2. copy our vertices array in a vertex buffer for OpenGL to use
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, _vertices_size_bytes, vertices, GL_STATIC_DRAW);

        //// 3. copy our index array in a element buffer for OpenGL to use
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_size_bytes, indices, GL_STATIC_DRAW);

        //// 4. then set the vertex attributes pointers (vertex semantic)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // 5. color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // unbind buffers, rebind explicitly when you want to draw this drawable
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Drawable_F3POSF3COL()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void bindContext()
    {
        shader.use();
        glBindVertexArray(VAO);
    }

    void draw()
    {
        glDrawElements(GL_TRIANGLES, indices_size_bytes, GL_UNSIGNED_INT, 0);
    }

private:
    float* vertices;
    uint32_t* indices;
    uint32_t vertices_size_bytes;
    uint32_t indices_size_bytes;
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;
};

class Drawable_F3POS : public Drawable
{
public:
    Drawable_F3POS(float* _vertices, uint32_t* _indices, uint32_t _vertices_size_bytes, uint32_t _indices_size_bytes)
        : vertices{ _vertices }, indices{ _indices }, vertices_size_bytes{ _vertices_size_bytes }, indices_size_bytes{ _indices_size_bytes }
    {
        // 1. bind Vertex Array Object
        // generate a Vertex Attribute Object
        // Core OpenGL requires that we use a VAO so it knows what to do with our vertex inputs.
        // If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // 2. copy our vertices array in a vertex buffer for OpenGL to use
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, _vertices_size_bytes, vertices, GL_STATIC_DRAW);

        //// 3. copy our index array in a element buffer for OpenGL to use
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_size_bytes, indices, GL_STATIC_DRAW);

        //// 4. then set the vertex attributes pointers (vertex semantic)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // unbind buffers, rebind explicitly when you want to draw this drawable
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Drawable_F3POS()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void bindContext()
    {
        shader.use();
        glBindVertexArray(VAO);
    }

    void draw()
    {
        glDrawElements(GL_TRIANGLES, indices_size_bytes, GL_UNSIGNED_INT, 0);
    }

private:
    float* vertices;
    uint32_t* indices;
    uint32_t vertices_size_bytes;
    uint32_t indices_size_bytes;
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;
};

}; // namespace radiance::drawable