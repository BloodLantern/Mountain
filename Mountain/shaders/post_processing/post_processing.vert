#version 460 core

layout (location = 0) in vec4 vertex; // vec2 position, vec2 textureCoordinates

uniform mat4 projection;

uniform vec2 imagePixelSize;
uniform vec2 position;
uniform vec2 scale;
uniform float rotation;

out vec2 uvs;

void main()
{
    uvs = vertex.zw;

    vec2 halfImagePixelSize = imagePixelSize * 0.5f;
    vec2 vertexPosition = vertex.xy;

    // Apply scale
    vertexPosition *= scale * halfImagePixelSize;

    // Apply rotation
    float c = cos(rotation), s = sin(rotation);
    vertexPosition = vec2(vertexPosition.x * c - vertexPosition.y * s, vertexPosition.x * s + vertexPosition.y * c);

    // And eventually translate the points to where the image should be drawn
    vertexPosition += position + halfImagePixelSize * scale;
    
    vec4 projectedPosition = projection * vec4(vertexPosition, 0.f, 1.f);
    gl_Position = vec4(projectedPosition.x, -projectedPosition.y, projectedPosition.zw);
}
