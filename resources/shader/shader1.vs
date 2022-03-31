#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 worldSpaceUpdateMatrix;
uniform mat4 modelMatrix;

void main()
{
    // inverted Y coord as part of LearnOpenGL exercise to make triangle upside down
    gl_Position = worldSpaceUpdateMatrix * modelMatrix * vec4(aPos.x, -aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}