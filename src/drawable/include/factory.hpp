#pragma once
#include "drawable.hpp"

namespace radiance::drawable
{

    enum VertexSemantic
    {
        F3POSF3COL = 0,
        F3POS = 1
    };

    class DrawableFactory
    {
    public:
        Drawable* createDrawable(
            VertexSemantic vertexSemantic,
            float* _vertices, uint32_t* _indices,
            uint32_t _vertices_size_bytes, uint32_t _indices_size_bytes)
        {
            switch (vertexSemantic) {
            case F3POSF3COL: // 3 floats for position, 3 floats for color
                return new Drawable_F3POSF3COL(_vertices, _indices, _vertices_size_bytes, _indices_size_bytes);
                break; //optional
            case F3POS: // 3 floats for position
                return new Drawable_F3POS(_vertices, _indices, _vertices_size_bytes, _indices_size_bytes);
                break; //optional

             // you can have any number of case statements.
            default: //Optional
                return nullptr;
            }
        }
    };

}; // namespace radiance::drawable