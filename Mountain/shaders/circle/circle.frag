#version 460 core

layout(origin_upper_left) in vec4 gl_FragCoord;

in vec2 circleCenter;
in float circleRadius;

uniform vec4 color;

uniform vec2 cameraScale;

out vec4 fragmentColor;

void main()
{
    vec2 centerToFragment = (gl_FragCoord.xy - circleCenter) / cameraScale;
    float centerToFragmentDistanceSquared = centerToFragment.x * centerToFragment.x + centerToFragment.y * centerToFragment.y;
    float centerSourceRadiusSquared = circleRadius * circleRadius;
    if (centerToFragmentDistanceSquared > centerSourceRadiusSquared)
        discard;
    
    fragmentColor = color;
}
