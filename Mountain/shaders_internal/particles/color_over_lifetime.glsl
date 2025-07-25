#include "common.glsl"

#include "../easing.glsl"

uniform struct ColorOverLifetime
{
    vec4 colorMin;
    vec4 colorMax;
    uint easingType;
} colorOverLifetime;

void ColorOverLifetimeUpdate(inout Particle particle)
{
    particle.color *= mix(
        colorOverLifetime.colorMin,
        colorOverLifetime.colorMax,
        EasingFromType(colorOverLifetime.easingType, 1.f - (particle.lifetime / particleLifetime))
    );
}
