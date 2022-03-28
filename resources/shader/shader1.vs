#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 transform;

void main()
{
    // inverted Y coord as part of LearnOpenGL exercise to make triangle upside down
    gl_Position = transform * vec4(aPos.x, -aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}