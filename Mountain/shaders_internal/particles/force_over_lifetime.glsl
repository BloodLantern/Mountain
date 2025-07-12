#include "common.glsl"

#include "../easing.glsl"

uniform struct ForceOverLifetime
{
    vec2 force;
    uint easingType;
} forceOverLifetime;

void ForceOverLifetimeUpdate(inout Particle particle)
{
    particle.velocity += forceOverLifetime.force * EasingFromType(forceOverLifetime.easingType, particle.lifetime / particleLifetime) * deltaTime;
}
