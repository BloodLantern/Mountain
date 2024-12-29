#version 460 core

#include "../common.glsl"

uniform mat4 projection;

uniform vec2 systemPosition;
uniform float systemRotation;

out flat int particleAlive;
out vec4 particleColor;

void main()
{
    particleAlive = int(liveParticles[gl_InstanceID]);

    if (particleAlive == 0) // If the particle is dead, we don't care about its vertex position as it will be discarded in the fragment shader anyway
        return;

    Particle particle = particles[gl_InstanceID];
    particleColor = particle.color;

    float c = cos(systemRotation), s = sin(systemRotation);
    vec2 rotatedOffset = vec2(particle.offset.x * c - particle.offset.y * s, particle.offset.x * s + particle.offset.y * c);

    gl_Position = vec4((projection * vec4(systemPosition + rotatedOffset, 0.f, 1.f)).xy, 0.f, 1.f);
}
