#version 460 core

layout (location = 0) in vec2 p1;
layout (location = 1) in vec2 p2;
layout (location = 2) in vec4 instanceColor;

uniform mat4 projection;

out vec4 color;

void main()
{
    color = instanceColor;

    vec2 pos;
    switch (gl_VertexID % 2)
    {
        case 0:
            pos = p1;
            break;

        case 1:
            pos = p2;
            break;
    }
    
    gl_Position = vec4((projection * vec4(pos, 0.f, 1.f)).xy, 0.f, 1.f);
}