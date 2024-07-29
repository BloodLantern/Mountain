#version 460 core

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec4 vertexColor;

uniform mat4 projection;

out vec4 color;

void main()
{
    color = vertexColor;
    gl_Position = vec4((projection * vec4(vertexPosition, 1.0, 1.0)).xy, 0.0, 1.0);
}
