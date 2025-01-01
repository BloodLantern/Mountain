#version 460

layout(origin_upper_left) in vec4 gl_FragCoord;

#include "../utils.glsl"

in vec2 center;
in vec2 size;
in vec2 angles; // startingAngle, deltaAngle
in vec4 color;
in flat int filled;

uniform vec2 cameraScale;

out vec4 fragmentColor;

void main()
{
    vec2 cameraScaleInverse = vec2(1.f) / cameraScale;
    vec2 centerToFragment = (gl_FragCoord.xy - center) * cameraScaleInverse;

    vec2 circleSize = size * cameraScaleInverse;

    vec2 temp = normalize(centerToFragment);
    float angle = atan(temp.y, temp.x);
    if (temp.y < 0.f)
        angle += Pi;

    // Discard the pixels outside of the arc angles
    if (angle < angles.x || angle > angles.x + angles.y)
        discard;

    float c = cos(angle), s = sin(angle);
    circleSize *= vec2(c, s);
    centerToFragment = abs(centerToFragment);

    // Discard the pixels outside the circle
    if (centerToFragment.x > circleSize.x && centerToFragment.y > circleSize.y)
        discard;

    // In case of a hollow circle, we also need to discard the pixels inside
    if (filled == 0)
    {
        if (centerToFragment.x + 1.f < circleSize.x || centerToFragment.y + 1.f < circleSize.y)
            discard;
    }

    fragmentColor = color;
}
