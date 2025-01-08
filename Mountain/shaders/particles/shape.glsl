#include "../utils.glsl"
#include "common.glsl"

const uint ShapeTypeCircle = 0;
const uint ShapeTypeLine = 1;
const uint ShapeTypeRectangle = 2;

const uint ShapeArcModeRandom = 0;
const uint ShapeArcModeLoop = 1;
const uint ShapeArcModePingPong = 2;
const uint ShapeArcModeBurstSpread = 3;

struct ShapeArc
{
    uint mode;
    float spread;
};

struct ShapeCircle
{
    float radius;
    // A value of 0 means the particles can only spawn on the edge of the radius, while 1 means they can spawn everywhere within the given radius
    float radiusThickness;
    // Angle in radians in the range [0, 2pi]
    float arcAngle;
    ShapeArc arc;
};

struct ShapeLine
{
    float radius;
    ShapeArc arc;
};

struct ShapeRectangle
{
    // See ShapeCircle::radiusThickness
    vec2 scaleThickness;
};

uniform struct Shape
{
    uint type;

    ShapeCircle circle;
    ShapeLine line;
    ShapeRectangle rectangle;

    vec2 offset;
    float rotation;
    vec2 scale;
} shape;

void ShapeInitialize(inout Particle particle)
{
    float id = float(gl_GlobalInvocationID.x) / float(gl_NumWorkGroups.x);
    vec2 randomSeed = vec2(id, fract(time * 0.1f));

    switch (shape.type)
    {
        case ShapeTypeCircle:
            vec2 randomPoint = RandomPointInCircle(randomSeed, vec2(0.f), 1.f);
            particle.offset = randomPoint * shape.circle.radius * shape.circle.radiusThickness + normalize(randomPoint) * shape.circle.radius * (1.f - shape.circle.radiusThickness);
            break;

        case ShapeTypeLine:
            break;

        case ShapeTypeRectangle:
            particle.offset = RandomPointInRectangle(randomSeed, shape.offset - shape.scale * 0.5f, shape.scale);
            break;
    }

    particle.offset = particle.offset * shape.scale + shape.offset;
    particle.velocity = normalize(particle.offset);
}
