#version 460 core

in flat int particleAlive;
in vec4 particleColor;

out vec4 fragmentColor;

void main()
{
    if (particleAlive == 0)
        discard;

    fragmentColor = particleColor;
}