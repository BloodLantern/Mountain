#include "common.glsl"

#include "../easing.glsl"

uniform struct ColorOverLifetime
{
    vec4 target;
    uint easingType;
} colorOverLifetime;

void ColorOverLifetimeUpdate(inout Particle particle)
{
    particle.color = mix(particleStartColor, colorOverLifetime.target, EasingFromType(colorOverLifetime.easingType, 1.f - (particle.lifetime / particleLifetime)));
}
