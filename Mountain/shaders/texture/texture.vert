#version 460 core

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in mat4 transformation;
layout (location = 5) in mat4 uvProjection;
layout (location = 9) in vec4 instanceColor;

uniform mat4 projection;

out vec2 textureCoordinates;
out vec4 color;

void main()
{
    vec4 position = vec4(vertexPosition, 0.f, 1.f);
    
    textureCoordinates = (uvProjection * position).xy;
    color = instanceColor;

    gl_Position = projection * (transformation * position);
}
