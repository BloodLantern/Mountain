
// Pseudo-random generator
float Random(vec2 seed) { return fract(sin(dot(seed, vec2(12.9898f, 78.233f))) * 43758.5453f); }

const float PositiveInfinity = 1.f / 0.f;
const float NegativeInfinity = -1.f / 0.f;
const float NaN = 0.f / 0.f;

const float Pi = 3.1415926535f;
const float TwoPi = Pi * 2.f;
const float PiOver2 = Pi / 2.f;
const float PiOver4 = Pi / 4.f;
const float Deg2Rad = Pi / 180.f;
const float Rad2Deg = 1.f / Deg2Rad;
