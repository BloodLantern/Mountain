#version 460

layout(origin_upper_left) in vec4 gl_FragCoord;

#include "../utils.glsl"

in vec2 center;
in vec2 size;
in vec2 scale;
in vec2 angles; // startingAngle, deltaAngle
in vec4 color;
in flat int filled;

uniform vec2 cameraScale;

out vec4 fragmentColor;

void main()
{
    vec2 cameraScaleInverse = vec2(1.f) / cameraScale;
    vec2 centerToFragment = gl_FragCoord.xy - center;

    vec2 circleSize = size;

    vec2 temp = centerToFragment * cameraScaleInverse;
    float angle = atan(temp.y, -temp.x) + Pi;

    float positiveStartingAngle = angles.x < 0.f ? angles.x + float(-int(angles.x / TwoPi) + 1) * TwoPi : angles.x;
    angle -= mod(positiveStartingAngle, TwoPi);
    if (angle < 0.f)
        angle += TwoPi;
    float maxAngle = min(angles.y, TwoPi);

    // Discard the pixels outside the arc angles
    if (angle < 0.f || angle > maxAngle)
        discard;

    vec2 centerToFragmentAbs = abs(centerToFragment) * cameraScaleInverse * cameraScaleInverse;
    temp = centerToFragmentAbs / scale;
    angle = atan(temp.y, temp.x);
    float c = cos(angle), s = sin(angle);
    circleSize *= vec2(c, s);

    // Discard the pixels outside the circle
    if (centerToFragmentAbs.x > circleSize.x && centerToFragmentAbs.y > circleSize.y)
        discard;

    // In case of a hollow circle, we also need to discard the pixels inside
    if (filled == 0 || angles.y == 0.f)
    {
        if (centerToFragmentAbs.x + 1.f < circleSize.x || centerToFragmentAbs.y + 1.f < circleSize.y || centerToFragmentAbs == vec2(0.f))
            discard;
    }

    fragmentColor = color;
}
