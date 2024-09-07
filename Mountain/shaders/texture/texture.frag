#version 460 core

in vec2 textureCoordinates;
in vec4 color;

uniform sampler2D image;

out vec4 fragmentColor;

void main()
{
    fragmentColor = color * texture(image, textureCoordinates);
} 
