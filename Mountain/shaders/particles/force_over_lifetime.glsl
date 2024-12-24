#include "common.glsl"

uniform struct ForceOverLifetime
{
    vec2 force;
} forceOverLifetime;

Particle ForceOverLifetimeUpdate(Particle particle)
{
    particle.velocity += forceOverLifetime.force * deltaTime;

    return particle;
}
