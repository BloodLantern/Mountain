#version 460 core

layout (location = 0) in vec2 p1;
layout (location = 1) in vec2 p2;
layout (location = 2) in vec2 p3;
layout (location = 3) in vec4 c1;
layout (location = 4) in vec4 c2;
layout (location = 5) in vec4 c3;

uniform mat4 projection;

out vec4 color;

void main()
{
    vec2 pos;
    switch (gl_VertexID % 3)
    {
        case 0:
            pos = p1;
            color = c1;
            break;

        case 1:
            pos = p2;
            color = c2;
            break;

        case 2:
            pos = p3;
            color = c3;
            break;
    }
    
    gl_Position = vec4((projection * vec4(pos, 0.f, 1.f)).xy, 0.f, 1.f);
}