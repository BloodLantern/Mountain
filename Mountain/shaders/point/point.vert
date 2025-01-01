#version 460

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 instanceColor;

uniform mat4 projection;

out vec4 color;

void main()
{
    color = instanceColor;

    gl_Position = vec4((projection * vec4(position, 0.f, 1.f)).xy, 0.f, 1.f);
}
