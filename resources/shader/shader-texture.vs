#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 worldSpaceUpdateMatrix;
uniform mat4 modelMatrix;

void main()
{
    gl_Position = worldSpaceUpdateMatrix * modelMatrix * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
}