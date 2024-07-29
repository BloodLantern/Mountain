#version 460 core

layout (location = 0) in vec2 position;

uniform mat4 projection;

void main()
{
    gl_Position = vec4((projection * vec4(position, 0.f, 1.f)).xy, 0.f, 1.f);
}
