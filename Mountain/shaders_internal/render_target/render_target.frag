#version 460

struct LightSource
{
    vec4 color;
    float intensity;
    float radius;
    float angleMin;
    float angleMax;
    vec2 position;
};

in vec2 textureCoordinates;
in vec2 fragmentPosition;

uniform mat4 camera;
uniform vec2 scale; // RenderTarget scale
uniform vec2 actualScale; // RenderTarget scale * Camera scale

uniform sampler2D framebuffer;
uniform vec4 color;
uniform vec4 ambientColor;

uniform int lightSourceCount;

layout(std430, binding = 0) readonly buffer Lights
{
    LightSource lightSources[];
};

out vec4 fragmentColor;

// TODO - Add bloom

float LightAttenuation(float x)
{
    float x2 = x * x;
    float inter = 1.f - 2.f * x2 + x2 * x2;
    return inter * inter;
}

void main()
{
    vec4 baseColor = color * texture(framebuffer, textureCoordinates);

    // Compute light color
    vec4 lightColor = ambientColor;
    for (int i = 0; i < lightSourceCount; i++)
    {
        LightSource lightSource = lightSources[i];
        vec2 lightSourcePosition = (camera * vec4(lightSource.position, 0.f, 1.f)).xy * scale;

        vec2 lightToFragment = (lightSourcePosition - fragmentPosition) / actualScale;
        float lightToFragmentDistanceSquared = lightToFragment.x * lightToFragment.x + lightToFragment.y * lightToFragment.y;
        float lightSourceRadiusSquared = lightSource.radius * lightSource.radius;
        if (lightToFragmentDistanceSquared > lightSourceRadiusSquared)
            continue;

        float attenuation = LightAttenuation(lightToFragmentDistanceSquared / lightSourceRadiusSquared);

        lightColor += lightSource.color * lightSource.intensity * attenuation;
    }

    // Clamp the light color components between 0 and 1
    lightColor = clamp(lightColor, vec4(0.f), vec4(1.f));

    fragmentColor = lightColor * baseColor;
}
