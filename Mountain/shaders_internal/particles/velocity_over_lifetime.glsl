#include "common.glsl"

#include "../easing.glsl"

uniform struct VelocityOverLifetime
{
    vec2 velocityMin;
    vec2 velocityMax;
    uint easingType;
} velocityOverLifetime;

void VelocityOverLifetimeUpdate(in Particle particle, inout vec2 velocity)
{
    velocity += mix(
        velocityOverLifetime.velocityMin,
        velocityOverLifetime.velocityMax,
        EasingFromType(velocityOverLifetime.easingType, 1.f - (particle.lifetime / particleLifetime))
    );
}
