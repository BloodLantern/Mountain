#version 460

in vec2 textureCoordinates;

uniform sampler2D text;
uniform vec4 color;

out vec4 fragmentColor;

void main()
{
    fragmentColor = color * vec4(1.0, 1.0, 1.0, texture(text, textureCoordinates).r);
}
