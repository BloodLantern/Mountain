#version 460 core

uniform vec4 color;

out vec4 fragmentColor;

void main()
{
    fragmentColor = color;
}
