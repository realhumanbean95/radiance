#pragma once
#include "drawable.hpp"

namespace radiance::drawable
{

    enum VertexSemantic
    {
        F3POSF3COL_INDEXED = 0,
        F3POS_INDEXED = 1,
        F3POSF2TEX_INDEXED = 2,
        F3POSF2TEX = 3
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
            case F3POSF3COL_INDEXED: // 3 floats for position, 3 floats for color
                return new Drawable_F3POSF3COL_Indexed(_vertices, _indices, _vertices_size_bytes, _indices_size_bytes);
                break; //optional
            case F3POS_INDEXED: // 3 floats for position
                return new Drawable_F3POS_Indexed(_vertices, _indices, _vertices_size_bytes, _indices_size_bytes);
                break; //optional
            case F3POSF2TEX_INDEXED: // 3 floats for position, 2 floats for texture coordinates
                return new Drawable_F3POSF2TEX_Indexed(_vertices, _indices, _vertices_size_bytes, _indices_size_bytes);
                break; //optional

             // you can have any number of case statements.
            default: //Optional
                return nullptr;
            }
        }

        Drawable* createDrawable(
            VertexSemantic vertexSemantic,
            float* _vertices,
            uint32_t _vertices_size_bytes)
        {
            switch (vertexSemantic) {
            case F3POSF2TEX: // 3 floats for position, 2 floats for texture coordinates, unindexed
                return new Drawable_F3POSF2TEX(_vertices, _vertices_size_bytes);
                break; //optional

             // you can have any number of case statements.
            default: //Optional
                return nullptr;
            }
        }
    };


}; // namespace radiance::drawable