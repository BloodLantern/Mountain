#version 460

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in mat4 transformation;
layout (location = 5) in vec2 instanceCenter;
layout (location = 6) in float instanceRadius;
layout (location = 7) in float instanceThickness;
layout (location = 8) in vec2 instanceScale;
layout (location = 9) in vec4 instanceColor;
layout (location = 10) in int instanceFilled;

uniform mat4 projection;
uniform mat4 camera;

uniform vec2 cameraScale;

out vec2 center;
out vec2 size;
out float thickness;
out vec2 scale;
out vec4 color;
out int filled;

void main()
{
    center = (camera * vec4(instanceCenter, 0.f, 1.f)).xy;
    size = instanceRadius * instanceScale;
    thickness = instanceThickness;
    scale = instanceScale;
    color = instanceColor;
    filled = instanceFilled;

    gl_Position = projection * transformation * vec4(vertexPosition, 0.f, 1.f);
}
