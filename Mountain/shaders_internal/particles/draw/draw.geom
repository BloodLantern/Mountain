#version 460

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VertexOut
{
    int particleAlive;
    float particleSize;
    vec4 particleColor;
} shaderIn[];

out GeometryOut
{
    vec4 particleColor;
    vec2 textureCoordinates;
} shaderOut;

uniform vec2 imageSizeNormalized; // Texture size in the range [0, 1])

void EmitVertexData(in vec4 position, in vec2 textureCoordinates)
{
    gl_Position = position;

    shaderOut.particleColor = shaderIn[0].particleColor;
    shaderOut.textureCoordinates = textureCoordinates;

    EmitVertex();
}

void main()
{
    if (shaderIn[0].particleAlive == 0) // If the particle is dead, don't create any vertices
        return;

    vec2 position = gl_in[0].gl_Position.xy;
    vec2 size = imageSizeNormalized * shaderIn[0].particleSize;
    vec2 halfSize = size * 0.5f;

    vec4 firstPosition = vec4(position.x - halfSize.x, position.y - halfSize.y, 0.f, 1.f);
    vec4 secondPosition = vec4(position.x + halfSize.x, position.y - halfSize.y, 0.f, 1.f);
    vec4 thirdPosition = vec4(position.x + halfSize.x, position.y + halfSize.y, 0.f, 1.f);
    vec4 fourthPosition = vec4(position.x - halfSize.x, position.y + halfSize.y, 0.f, 1.f);

    EmitVertexData(secondPosition, vec2(1.f, 0.f));
    EmitVertexData(firstPosition, vec2(0.f, 0.f));
    EmitVertexData(thirdPosition, vec2(1.f, 1.f));

    EmitVertexData(fourthPosition, vec2(0.f, 1.f));

    EndPrimitive();
}
