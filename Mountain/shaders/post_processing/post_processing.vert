#version 460 core

layout (location = 0) in vec4 vertex; // vec2 position, vec2 textureCoordinates

uniform mat4 projection;

uniform vec2 halfImagePixelSize;
uniform vec2 position;
uniform vec2 scale;
uniform float rotation;

uniform mat2 diagonalFlip;
uniform mat2 antiDiagonalFlip;

out vec2 textureCoordinates;

void main()
{
    textureCoordinates = vec2(vertex.z, 1.f - vertex.w);

    vec2 vertexPosition = vertex.xy;

    // Apply scaling
    vertexPosition *= scale * halfImagePixelSize;

    // Apply diagonal flipping
    vertexPosition = diagonalFlip * vertexPosition;
    vertexPosition = antiDiagonalFlip * vertexPosition;

    // Apply rotation
    float c = cos(rotation), s = sin(rotation);
    vertexPosition = vec2(vertexPosition.x * c - vertexPosition.y * s, vertexPosition.x * s + vertexPosition.y * c);

    // And eventually translate the points to where the image should be drawn
    vertexPosition += position + halfImagePixelSize * scale;

    gl_Position = projection * vec4(vertexPosition, 0.f, 1.f);
}
