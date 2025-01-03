#include "../utils.glsl"
#include "common.glsl"

const uint ShapeTypeCircle = 0;

uniform struct Shape
{
    uint type;
} shape;

void ShapeInitialize(inout Particle particle)
{
    float id = float(gl_GlobalInvocationID.x) / float(gl_NumWorkGroups.x);
    float r = Random(vec2(id, fract(time)));
    float r2 = Random(vec2(r, id));

    particle.velocity = normalize(vec2(r, r2) * 2.f - vec2(1.f));
}
