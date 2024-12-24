#include "common.glsl"
#include "../easing.glsl"

uniform struct ColorOverLifetime
{
    vec4 target;
} colorOverLifetime;

Particle ColorOverLifetimeUpdate(Particle particle)
{
    particle.color = mix(particleStartColor, colorOverLifetime.target, 1.f - (particle.lifetime / particleLifetime));
    return particle;
}
