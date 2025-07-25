#version 460

#include "../common.glsl"

out VertexOut
{
    int particleAlive;
    float particleSize;
    vec4 particleColor;
} shaderOut;

uniform mat4 projection;

uniform vec2 systemPosition;
uniform float systemRotation;

void main()
{
    shaderOut.particleAlive = int(liveParticles[gl_InstanceID]);

    // If the particle is dead, we don't care about its vertex position as it will be discarded in the geometry/fragment shader anyway
    if (shaderOut.particleAlive == 0)
        return;

    Particle particle = particles[gl_InstanceID];
    shaderOut.particleSize = particle.size;
    shaderOut.particleColor = particle.color;

    float c = cos(systemRotation), s = sin(systemRotation);
    vec2 rotatedOffset = vec2(particle.offset.x * c - particle.offset.y * s, particle.offset.x * s + particle.offset.y * c);

    gl_Position = vec4((projection * vec4(systemPosition + rotatedOffset, 0.f, 1.f)).xy, 0.f, 1.f);
}
