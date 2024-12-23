#include "common.glsl"
#include "../easing.glsl"

uniform struct ColorOverLifetime
{
    vec4 start, end;
    uint easing; // From the Easing::Type enum, see utils.glsl
} colorOverLifetime;

Particle ColorOverLifetimeUpdate(Particle particle)
{
    particle.color = mix(colorOverLifetime.start, colorOverLifetime.end, 1.f - (particle.lifetime / particleLifetime));
    // TODO - Easing

    return particle;
}
