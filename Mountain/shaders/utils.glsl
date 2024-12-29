
// Pseudo-random generator
float Random(vec2 seed) { return fract(sin(dot(seed, vec2(12.9898f, 78.233f))) * 43758.5453f); }

const float PositiveInfinity = 1.f / 0.f;
const float NegativeInfinity = -1.f / 0.f;
const float NaN = 0.f / 0.f;
