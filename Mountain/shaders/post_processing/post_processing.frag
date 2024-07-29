#version 460 core

in vec2 uvs;

uniform sampler2D framebuffer;

out vec4 fragmentColor;

// TODO - Add lighting
// TODO - Add bloom
void main()
{
    fragmentColor = texture(framebuffer, uvs);
}
