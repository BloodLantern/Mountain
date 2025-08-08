#include "common.glsl"

#include "../easing.glsl"

uniform struct ForceOverLifetime
{
    vec2 forceMin;
    vec2 forceMax;
    uint easingType;
} forceOverLifetime;

void ForceOverLifetimeUpdate(in Particle particle, inout vec2 accumulatedVelocity)
{
    accumulatedVelocity += mix(
        forceOverLifetime.forceMin,
        forceOverLifetime.forceMax,
        EasingFromType(forceOverLifetime.easingType, 1.f - (particle.lifetime / particleLifetime))
    ) * deltaTime;
}
