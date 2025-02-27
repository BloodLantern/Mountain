#include "common.glsl"
#include "../easing.glsl"

uniform struct ColorOverLifetime
{
    vec4 target;
    // TODO - Easing
} colorOverLifetime;

void ColorOverLifetimeUpdate(inout Particle particle)
{
    particle.color = mix(particleStartColor, colorOverLifetime.target, 1.f - (particle.lifetime / particleLifetime));
}
