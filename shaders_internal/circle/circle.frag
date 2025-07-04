#version 460

layout(origin_upper_left) in vec4 gl_FragCoord;

in vec2 center;
in vec2 size;
in flat float thickness;
in vec2 scale;
in vec4 color;
in flat int filled;

uniform vec2 cameraScale;

out vec4 fragmentColor;

void main()
{
    vec2 cameraScaleInverse = vec2(1.f) / cameraScale;
    vec2 centerToFragment = abs(gl_FragCoord.xy - center) * cameraScaleInverse * cameraScaleInverse;

    vec2 circleSize = size;

    vec2 temp = centerToFragment / scale;
    float angle = atan(temp.y, temp.x);
    float c = cos(angle), s = sin(angle);
    vec2 cosSin = vec2(c, s);

    float halfThickness = thickness * 0.5f;
    vec2 circleSizeExt = (circleSize + vec2(halfThickness)) * cosSin;
    vec2 circleSizeIn = (circleSize - vec2(halfThickness)) * cosSin;

    // Discard the pixels outside the circle
    if (
        centerToFragment.x > circleSizeExt.x &&
        centerToFragment.y > circleSizeExt.y
    )
    {
        discard;
    }

    // In case of a hollow circle, we also need to discard the pixels inside
    if (filled == 0)
    {
        if (
            centerToFragment.x + 1.f < circleSizeIn.x ||
            centerToFragment.y + 1.f < circleSizeIn.y ||
            centerToFragment == vec2(0.f)
        )
        {
            discard;
        }
    }

    fragmentColor = color;
}
