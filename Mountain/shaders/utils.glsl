
// Pseudo-random generator for any given position
float Random(vec2 position) { return fract(sin(dot(position, vec2(12.9898f, 78.233f))) * 43758.5453f); }
