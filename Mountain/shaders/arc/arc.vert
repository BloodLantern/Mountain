#version 460

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in mat4 transformation;
layout (location = 5) in vec2 instanceCenter;
layout (location = 6) in float instanceRadius;
layout (location = 7) in float instanceStartingAngle;
layout (location = 8) in float instanceDeltaAngle;
layout (location = 9) in vec2 instanceScale;
layout (location = 10) in vec4 instanceColor;
layout (location = 11) in int instanceFilled;

uniform mat4 projection;
uniform mat4 camera;

out vec2 center;
out vec2 size;
out vec2 angles; // startingAngle, deltaAngle
out vec4 color;
out int filled;

void main()
{
    center = (camera * vec4(instanceCenter, 0.f, 1.f)).xy;
    size = instanceRadius * instanceScale;
    angles = vec2(instanceStartingAngle, instanceDeltaAngle);
    color = instanceColor;
    filled = instanceFilled;

    gl_Position = projection * transformation * vec4(vertexPosition, 0.f, 1.f);
}
