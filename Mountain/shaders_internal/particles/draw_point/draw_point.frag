#version 460

in VertexOut
{
    flat int particleAlive;
    flat vec4 particleColor;
} shaderIn;

out vec4 outFragmentColor;

void main()
{
    if (shaderIn.particleAlive == 0)
        discard;

    outFragmentColor = shaderIn.particleColor;
}
