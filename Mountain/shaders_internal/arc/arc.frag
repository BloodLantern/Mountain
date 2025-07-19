#version 460

layout(origin_upper_left) in vec4 gl_FragCoord;

#include "../utils.glsl"

in flat vec2 center;
in flat vec2 size;
in flat vec2 scale;
in flat vec2 angles; // startingAngle, deltaAngle // both are in the range [0, TwoPi)
in flat float thickness;
in flat vec4 color;
in flat int filled;

uniform vec2 cameraScale;

out vec4 fragmentColor;

void main()
{
    vec2 cameraScaleInverse = vec2(1.f) / cameraScale;
    vec2 centerToFragment = gl_FragCoord.xy - center;

    vec2 circleSize = size; // = radius * scale

    vec2 temp = -centerToFragment * cameraScaleInverse;
    float angle = atan(temp.y, temp.x);

    angle = RemapValue(angle, -Pi, Pi, 0.f, TwoPi);

    if (angles.x + angles.y > TwoPi)
    {
        if (angle + TwoPi > angles.x + angles.y && angle < angles.x)
            discard;
    }
    else
    {
        float maxAngle = min(angles.x + angles.y, TwoPi);

        // Discard the pixels outside the arc angles
        if ((angles.x > 0.f && angle < angles.x) || (angles.x + angles.y < TwoPi && angle > maxAngle))
            discard;
    }

    // FIXME - Angle is "incorrect" when scaled on one axis.
    // It is actually technically correct, but to be consistent with how we spawn the particles in an arc shape (shape.glsl),
    // we should instead apply the scale AFTER and not before.

    vec2 centerToFragmentAbs = abs(centerToFragment) * cameraScaleInverse * cameraScaleInverse;
    temp = centerToFragmentAbs / scale;
    angle = atan(temp.y, temp.x);
    float c = cos(angle), s = sin(angle);
    vec2 cosSin = vec2(c, s);

    float halfThickness = thickness * 0.5f;
    vec2 circleSizeOuter = (circleSize + vec2(halfThickness)) * cosSin;
    vec2 circleSizeInner = (circleSize - vec2(halfThickness)) * cosSin;

    vec2 circleSizeDifference = circleSizeOuter - circleSizeInner;

    // For small thickness and high scale on one axis, we might miss some pixels, so we make sure to have at least one pixel everywhere
    if (circleSizeDifference.x < 0.5f)
    {
        circleSizeOuter.x += -circleSizeDifference.x + 1.f;
        circleSizeInner.x -= -circleSizeDifference.x + 1.f;
    }
    if (circleSizeDifference.y < 0.5f)
    {
        circleSizeOuter.y += -circleSizeDifference.y + 1.f;
        circleSizeInner.y -= -circleSizeDifference.y + 1.f;
    }

    // Discard the pixels outside the circle
    if (centerToFragmentAbs.x > circleSizeOuter.x || centerToFragmentAbs.y > circleSizeOuter.y)
        discard;

    // In case of a hollow circle, we also need to discard the pixels inside
    if (filled == 0 && (centerToFragmentAbs.x < circleSizeInner.x || centerToFragmentAbs.y < circleSizeInner.y))
        discard;

    fragmentColor = color;
}
