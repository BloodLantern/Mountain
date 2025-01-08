#include "common.glsl"

uniform struct ForceOverLifetime
{
    vec2 force;
} forceOverLifetime;

void ForceOverLifetimeUpdate(inout Particle particle)
{
    particle.velocity += forceOverLifetime.force * deltaTime;
}
