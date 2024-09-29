#version 460 core

struct LightSourceData
{
    vec4 color;
    float intensity;
    float radius;
    float angleMin;
    float angleMax;
    vec2 position;
};

const uint MaxLightSources = 50;

in vec2 textureCoordinates;
in vec2 fragmentPosition;

uniform vec2 actualScale; // Camera scale * RenderTarget scale

uniform sampler2D framebuffer;
uniform vec4 color;
uniform vec4 ambientColor;

uniform int lightSourceCount;
uniform LightSourceData lightSources[MaxLightSources];

out vec4 fragmentColor;

// TODO - Add bloom
// TODO - Add screen shake

float attenuate(float x)
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
        LightSourceData lightSource = lightSources[i];
        
        vec2 lightToFragment = (lightSource.position - fragmentPosition) / actualScale;
        float lightToFragmentDistanceSquared = lightToFragment.x * lightToFragment.x + lightToFragment.y * lightToFragment.y;
        float lightSourceRadiusSquared = lightSource.radius * lightSource.radius;
        if (lightToFragmentDistanceSquared > lightSourceRadiusSquared)
            continue;
        
        float attenuation = attenuate(lightToFragmentDistanceSquared / lightSourceRadiusSquared);
        
        lightColor += lightSource.color * lightSource.intensity * attenuation;
    }
    
    // Clamp the light color components between 0 and 1
    lightColor = clamp(lightColor, vec4(0.f), vec4(1.f));
    
    fragmentColor = lightColor * baseColor;
}
