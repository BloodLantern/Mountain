#version 460

in GeometryOut
{
    flat vec4 particleColor;
    vec2 textureCoordinates;
} shaderIn;

out vec4 outFragmentColor;

uniform sampler2D image;

void main()
{
    outFragmentColor = shaderIn.particleColor * texture(image, shaderIn.textureCoordinates);
}
