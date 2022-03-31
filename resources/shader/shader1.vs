#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 modelMatrixUpdate;

void main()
{
    // inverted Y coord as part of LearnOpenGL exercise to make triangle upside down
    gl_Position = projectionMatrix * viewMatrix * modelMatrixUpdate* modelMatrix * vec4(aPos.x, -aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}