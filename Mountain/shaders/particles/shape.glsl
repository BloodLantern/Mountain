#include "../utils.glsl"
#include "common.glsl"

const uint ShapeTypeCircle = 0;

uniform struct Shape
{
    uint type;
} shape;

void ShapeInitialize(inout Particle particle)
{
    float r = Random(vec2(gl_GlobalInvocationID.x, time));
    float r2 = Random(vec2(r, time));

    particle.velocity = normalize(vec2(r, r2) * 2.f - vec2(1.f));
}
