
// Pseudo-random generator
float Random(vec2 seed) { return fract(sin(dot(seed, vec2(12.9898f, 78.233f))) * 43758.5453f); }
