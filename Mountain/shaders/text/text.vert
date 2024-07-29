#version 460 core

layout (location = 0) in vec4 vertex; // vec2 position, vec2 textureCoordinates

uniform mat4 projection;

out vec2 uvs;

void main()
{
    uvs = vertex.zw;
    
    gl_Position = vec4((projection * vec4(vertex.xy, 0.f, 1.f)).xy, 0.f, 1.f);
}
