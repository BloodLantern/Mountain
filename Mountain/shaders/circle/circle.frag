#version 460 core

layout(origin_upper_left) in vec4 gl_FragCoord;

in vec2 circleCenter;
in float circleRadius;

uniform vec4 color;

out vec4 fragmentColor;

void main()
{
    if (length(gl_FragCoord.xy - circleCenter) > circleRadius)
        discard;
    
    fragmentColor = color;
}
