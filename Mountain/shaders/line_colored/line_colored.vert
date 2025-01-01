#version 460

layout (location = 0) in vec2 p1;
layout (location = 1) in vec2 p2;
layout (location = 2) in vec4 c1;
layout (location = 3) in vec4 c2;

uniform mat4 projection;

out vec4 color;

void main()
{
    vec2 pos;
    switch (gl_VertexID % 2)
    {
        case 0:
            pos = p1;
            color = c1;
            break;
        
        case 1:
            pos = p2;
            color = c2;
            break;
    }
    
    gl_Position = vec4((projection * vec4(pos, 0.f, 1.f)).xy, 0.f, 1.f);
}
