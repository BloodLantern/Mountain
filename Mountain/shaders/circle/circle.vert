#version 460 core

layout (location = 0) in vec2 vertexPosition;

uniform mat4 projection;

uniform vec2 position;
uniform float radius;

out vec2 circleCenter;
out float circleRadius;

void main()
{
    circleCenter = position;
    circleRadius = radius;

    gl_Position = projection * vec4(vertexPosition, 0.f, 1.f);
}
