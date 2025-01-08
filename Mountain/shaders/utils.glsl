
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
            break;
        point = RandomPointInRectangle(fract((seed + vec2(1.f)) * point), vec2(-1.f), vec2(2.f));
    }

    return center + point * radius;
}

vec2 RandomPointInCircle(in vec2 seed, in vec2 center, in float radius, in vec2 scale)
{
    return RandomPointInCircle(seed, vec2(0.f), radius) * scale + center;
}

vec2 RandomDirection(in vec2 seed)
{
    float angle = RandomFloat(seed, 0.f, TwoPi);
    return vec2(cos(angle), sin(angle));
}
