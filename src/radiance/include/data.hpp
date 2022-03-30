#pragma once

#include <array>

// verts for a triangle
float vertices1[] = {
    // positions       // colors
   -0.5f, -0.5f, 0.0f,  0.18f, 0.01f, 0.31f,   // bottom right
    0.5f, -0.5f, 0.0f,  0.97f, 0.67f, 0.32f,   // bottom left
    0.0f,  0.5f, 0.0f,  0.96f, 0.18f, 0.59f    // top 
};

uint32_t indices1[] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
};


// verts for a quad
float vertices2[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
unsigned int indices2[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};


std::array<std::array<float, 3>, 10> objectPositions = {
        std::array<float, 3>{0.0f,  0.0f,  0.0f},
        std::array<float, 3>{2.0f,  5.0f, -15.0f},
        std::array<float, 3>{-1.5f, -2.2f, -2.5f},
        std::array<float, 3>{-3.8f, -2.0f, -12.3f},
        std::array<float, 3>{2.4f, -0.4f, -3.5f},
        std::array<float, 3>{-1.7f,  3.0f, -7.5f},
        std::array<float, 3>{1.3f, -2.0f, -2.5f},
        std::array<float, 3>{1.5f,  2.0f, -2.5f},
        std::array<float, 3>{1.5f,  0.2f, -1.5f},
        std::array<float, 3>{-1.3f,  1.0f, -1.5f}
};
