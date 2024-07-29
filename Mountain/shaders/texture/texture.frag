#version 460 core

in vec2 uvs;

uniform sampler2D image;
uniform vec4 color;

out vec4 fragmentColor;

void main()
{
    fragmentColor = color * texture(image, uvs);
} 
