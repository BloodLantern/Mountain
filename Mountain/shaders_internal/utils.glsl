
const float PositiveInfinity = 1.f / 0.f;
const float NegativeInfinity = -1.f / 0.f;
const float NaN = 0.f / 0.f;

const float Pi = 3.1415926535f;
const float TwoPi = Pi * 2.f;
const float PiOver2 = Pi / 2.f;
const float PiOver4 = Pi / 4.f;

const float Deg2Rad = Pi / 180.f;
const float Rad2Deg = 1.f / Deg2Rad;

float SquaredLength(in vec2 value) { return value.x * value.x + value.y * value.y; }

float RemapValue(in float oldValue, in vec2 oldRange, in vec2 newRange)
{
    return (oldValue - oldRange.x) * (newRange.y - newRange.x) / (oldRange.y - oldRange.x) + newRange.x;
}

vec2 Rotated(in vec2 value, in float c, in float s)
{
    return vec2(value.x * c - value.y * s, value.x * s + value.y * c);
}

vec2 Rotated(in vec2 value, in float angle) { return Rotated(value, cos(angle), sin(angle)); }

// Pseudo-random generator
// Returns a float in the range [0, 1]
// Source: https://stackoverflow.com/a/4275343/19269811
float Random(in vec2 seed) { return fract(sin(dot(seed, vec2(12.9898f, 78.233f))) * 43758.5453f); }

float RandomFloat(in vec2 seed, in float minimum, in float maximum) { return Random(seed) * (maximum - minimum) + minimum; }

vec2 RandomPointInRectangle(in vec2 seed, in vec2 topLeftPosition, in vec2 size)
{
    float x = RandomFloat(seed, topLeftPosition.x, topLeftPosition.x + size.x);
    float y = RandomFloat(vec2(seed.x * seed.y, x), topLeftPosition.y, topLeftPosition.y + size.y);
    return vec2(x, y);
}

vec2 RandomPointInCircle(in vec2 seed, in vec2 center, in float radius)
{
    // See https://youtu.be/4y_nmpv-9lI
    vec2 point = RandomPointInRectangle(seed, vec2(-1.f), vec2(2.f));
    for (int i = 0; i < 10; i++)
    {
        if (SquaredLength(point) < 1.f)
            return center + point * radius;
        point = RandomPointInRectangle(fract((seed + vec2(1.f)) * point), vec2(-1.f), vec2(2.f));
    }

    return center;
}

vec2 RandomPointInCircle(in vec2 seed, in vec2 center, in float radius, in vec2 scale)
{
    return RandomPointInCircle(seed, vec2(0.f), radius) * scale + center;
}

vec2 RandomPointInArc(in vec2 seed, in vec2 center, in float radius, in float arcAngle)
{
    vec2 pointInCircle = RandomPointInCircle(seed, vec2(0.f), 1.f);
    float pointAngle = atan(pointInCircle.y, pointInCircle.x);
    float newPointAngle = RemapValue(pointAngle, vec2(-Pi, Pi), vec2(0.f, arcAngle));
    return Rotated(pointInCircle, newPointAngle - pointAngle) * vec2(1.f, -1.f) * radius + center;
}

vec2 RandomPointInArc(in vec2 seed, in vec2 center, in float radius, in float arcAngle, in vec2 scale)
{
    return RandomPointInArc(seed, vec2(0.f), radius, arcAngle) * scale + center;
}

vec2 RandomDirection(in vec2 seed)
{
    float angle = RandomFloat(seed, 0.f, TwoPi);
    return vec2(cos(angle), sin(angle));
}
