#version 460 core

layout(origin_upper_left) in vec4 gl_FragCoord;

in vec2 center;
in float radius;
in vec4 color;
in flat int filled;

uniform vec2 cameraScale;

out vec4 fragmentColor;

void main()
{
    vec2 cameraScaleInverse = vec2(1.f) / cameraScale;
    vec2 centerToFragment = abs(gl_FragCoord.xy - center) * cameraScaleInverse;

    vec2 circleSize = radius * cameraScaleInverse;

    vec2 temp = normalize(centerToFragment);
    float angle = atan(temp.y, temp.x);
    float c = cos(angle), s = sin(angle);
    circleSize *= vec2(c, s);

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
