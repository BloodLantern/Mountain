#version 460 core

layout (location = 0) in vec2 vertexPosition;

uniform mat4 projection;

uniform mat4 transformation;
uniform mat4 uvProjection;

out vec2 textureCoordinates;
out vec2 fragmentPosition;

void main()
{
    vec4 position = vec4(vertexPosition, 0.f, 1.f);
    
    textureCoordinates = ((uvProjection * position).xy + vec2(1.f)) * 0.5f;
    textureCoordinates.y = 1.f - textureCoordinates.y;

    vec4 transformedPosition = transformation * position;
    
    fragmentPosition = transformedPosition.xy;
    
    gl_Position = projection * transformedPosition;
}
