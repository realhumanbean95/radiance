#version 430 core
layout (location = 0) in vec3 aPos;

out vec3 ourColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    ourColor = vec3(0.0, 1.0, 0.0);
}