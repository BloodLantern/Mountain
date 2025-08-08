#include "common.glsl"

#include "../easing.glsl"
#include "../utils.glsl"

uniform struct ColorBySpeed
{
    vec4 colorMin;
    vec4 colorMax;
    float speedMin;
    float speedMax;
    uint easingType;
} colorBySpeed;

void ColorBySpeedUpdate(inout Particle particle, in float speed)
{
    particle.color *= mix(
        colorBySpeed.colorMin,
        colorBySpeed.colorMax,
        EasingFromType(
            colorBySpeed.easingType,
            clamp(
                RemapValue(
                    speed,
                    colorBySpeed.speedMin * colorBySpeed.speedMin,
                    colorBySpeed.speedMax * colorBySpeed.speedMax,
                    0.f,
                    1.f
                ),
                0.f,
                1.f
            )
        )
    );
}
