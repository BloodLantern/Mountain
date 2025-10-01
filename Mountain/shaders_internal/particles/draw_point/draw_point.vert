#version 460

#include "../common.glsl"
#include "../../utils.glsl"

out VertexOut
{
    int particleAlive;
    vec4 particleColor;
} shaderOut;

uniform mat4 projection;

uniform vec2 systemPosition;
uniform vec2 systemRotation; // float cosRotation, float sinRotation

void main()
{
    shaderOut.particleAlive = int(liveParticles[gl_InstanceID]);

    // If the particle is dead, we don't care about its vertex position as it will be discarded in the geometry/fragment shader anyway
    if (shaderOut.particleAlive == 0)
    {
        gl_Position = vec4(0.f, 0.f, 0.f, 1.f);
        gl_PointSize = 0.f;
        return;
    }

    Particle particle = particles[gl_InstanceID];
    shaderOut.particleColor = particle.color;

    vec2 rotatedOffset = Rotated(particle.offset, systemRotation);

    gl_Position = vec4((projection * vec4(systemPosition + rotatedOffset, 0.f, 1.f)).xy, 0.f, 1.f);
    gl_PointSize = particle.size;
}
