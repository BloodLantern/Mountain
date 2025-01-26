
struct Particle
{
    float lifetime;
    //int padding0[3]; implicit padding here

    vec2 offset;
    vec2 velocity;
    vec4 color;
};

layout(std430, binding = 0) coherent buffer AliveParticles
{
    bool liveParticles[]; // true if the particle is alive and should be updated and drawn
};

layout(std430, binding = 1) buffer Particles
{
    Particle particles[];
};

uniform uint particleCount;
uniform float deltaTime;

uniform float particleLifetime;
uniform float particleSpeed;
uniform vec4 particleStartColor;
