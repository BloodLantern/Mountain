
#include "utils.glsl"

// Easing::Type enum
const uint EasingTypeLinear = 0;
const uint EasingTypeSineIn = 1;
const uint EasingTypeSineOut = 2;
const uint EasingTypeSineInOut = 3;
const uint EasingTypeQuadIn = 4;
const uint EasingTypeQuadOut = 5;
const uint EasingTypeQuadInOut = 6;
const uint EasingTypeCubicIn = 7;
const uint EasingTypeCubicOut = 8;
const uint EasingTypeCubicInOut = 9;
const uint EasingTypeQuartIn = 10;
const uint EasingTypeQuartOut = 11;
const uint EasingTypeQuartInOut = 12;
const uint EasingTypeQuintIn = 13;
const uint EasingTypeQuintOut = 14;
const uint EasingTypeQuintInOut = 15;
const uint EasingTypeExpoIn = 16;
const uint EasingTypeExpoOut = 17;
const uint EasingTypeExpoInOut = 18;
const uint EasingTypeCircIn = 19;
const uint EasingTypeCircOut = 20;
const uint EasingTypeCircInOut = 21;
const uint EasingTypeBackIn = 22;
const uint EasingTypeBackOut = 23;
const uint EasingTypeBackInOut = 24;
const uint EasingTypeElasticIn = 25;
const uint EasingTypeElasticOut = 26;
const uint EasingTypeElasticInOut = 27;
const uint EasingTypeBounceIn = 28;
const uint EasingTypeBounceOut = 29;
const uint EasingTypeBounceInOut = 30;

float EasingLinear(in float t) { return t; }

float EasingSineIn(in float t) { return sin(PiOver2 * t); }

float EasingSineOut(in float t) { return 1.f + sin(PiOver2 * (t - 1)); }

float EasingSineInOut(in float t) { return 0.5f * (1.f + sin(Pi * (t - 0.5f))); }

float EasingQuadIn(in float t) { return t * t; }

float EasingQuadOut(in float t) { return t * (2.f - t); }

float EasingQuadInOut(in float t) { return t < 0.5f ? 2.f * t * t : t * (4.f - 2.f * t) - 1.f; }

float EasingCubicIn(in float t)
{
    return t * t * t;
}

float EasingCubicOut(in float t)
{
    t--;
    return 1.f + t * t * t;
}

float EasingCubicInOut(in float t)
{
    const float t2 = t - 1;
    const float t3 = t2 - 1;
    return t < 0.5f ? 4.f * t * t * t : 1.f + t2 * (2.f * t3) * (2.f * t3);
}

float EasingQuartIn(in float t)
{
    t *= t;
    return t * t;
}

float EasingQuartOut(in float t)
{
    float t2 = t - 1;
    t2 *= t2;
    return 1.f - t2 * t2;
}

float EasingQuartInOut(in float t)
{
    if (t < 0.5f)
    {
        t *= t;
        return 8.f * t * t;
    }
    else
    {
        t -= 1;
        t = t * t;
        return 1.f - 8.f * t * t;
    }
}

float EasingQuintIn(in float t)
{
    const float t2 = t * t;
    return t * t2 * t2;
}

float EasingQuintOut(in float t)
{
    t -= 1;
    const float t2 = t * t;
    return 1.f + t * t2 * t2;
}

float EasingQuintInOut(in float t)
{
    float t2;
    if (t < 0.5f)
    {
        t2 = t * t;
        return 16.f * t * t2 * t2;
    }
    else
    {
        t -= 1;
        t2 = t * t;
        return 1.f + 16.f * t * t2 * t2;
    }
}

float EasingExpoIn(in float t)
{
    return (pow(2.f, 8.f * t) - 1.f) / 255.f;
}

float EasingExpoOut(in float t)
{
    return 1.f - pow(2.f, -8.f * t);
}

float EasingExpoInOut(in float t)
{
    if (t < 0.5f)
        return (pow(2.f, 16.f * t) - 1.f) / 510.f;

    return 1.f - 0.5f * pow(2.f, -16.f * (t - 0.5f));
}

float EasingCircIn(in float t)
{
    return 1.f - sqrt(1.f - t);
}

float EasingCircOut(in float t)
{
    return sqrt(t);
}

float EasingCircInOut(in float t)
{
    if (t < 0.5f)
        return (1.f - sqrt(1.f - 2.f * t)) * 0.5f;

    return (1.f + sqrt(2.f * t - 1.f)) * 0.5f;
}

float EasingBackIn(in float t)
{
    return t * t * (2.70158f * t - 1.70158f);
}

float EasingBackOut(in float t)
{
    t -= 1;
    return 1.f + t * t * (2.70158f * t + 1.70158f);
}

float EasingBackInOut(in float t)
{
    if (t < 0.5f)
    {
        return t * t * (7.f * t - 2.5f) * 2.f;
    }
    else
    {
        t -= 1;
        return 1.f + t * t * 2.f * (7.f * t + 2.5f);
    }
}

float EasingElasticIn(in float t)
{
    const float t2 = t * t;
    return t2 * t2 * sin(t * Pi * 4.5f);
}

float EasingElasticOut(in float t)
{
    const float t2 = (t - 1.f) * (t - 1.f);
    return 1.f - t2 * t2 * cos(t * Pi * 4.5f);
}

float EasingElasticInOut(in float t)
{
    float t2;
    if (t < 0.45f)
    {
        t2 = t * t;
        return 8.f * t2 * t2 * sin(t * Pi * 9.f);
    }

    if (t < 0.55f)
        return 0.5f + 0.75f * sin(t * Pi * 4.f);

    t2 = (t - 1.f) * (t - 1.f);
    return 1.f - 8.f * t2 * t2 * sin(t * Pi * 9.f);
}

float EasingBounceIn(in float t)
{
    return pow(2.f, 6.f * (t - 1.f)) * abs(sin(t * Pi * 3.5f));
}

float EasingBounceOut(in float t)
{
    return 1.f - pow(2.f, -6.f * t) * abs(cos(t * Pi * 3.5f));
}

float EasingBounceInOut(in float t)
{
    if (t < 0.5f)
        return 8.f * pow(2.f, 8.f * (t - 1.f)) * abs(sin(t * Pi * 7.f));

    return 1.f - 8.f * pow(2.f, -8.f * t) * abs(sin(t * Pi * 7.f));
}

float EasingFromType(in uint type, in float t)
{
    switch (type)
    {
        case EasingTypeLinear: return EasingLinear(t);
        case EasingTypeSineIn: return EasingSineIn(t);
        case EasingTypeSineOut: return EasingSineOut(t);
        case EasingTypeSineInOut: return EasingSineInOut(t);
        case EasingTypeQuadIn: return EasingQuadIn(t);
        case EasingTypeQuadOut: return EasingQuadOut(t);
        case EasingTypeQuadInOut: return EasingQuadInOut(t);
        case EasingTypeCubicIn: return EasingCubicIn(t);
        case EasingTypeCubicOut: return EasingCubicOut(t);
        case EasingTypeCubicInOut: return EasingCubicInOut(t);
        case EasingTypeQuartIn: return EasingQuartIn(t);
        case EasingTypeQuartOut: return EasingQuartOut(t);
        case EasingTypeQuartInOut: return EasingQuartInOut(t);
        case EasingTypeQuintIn: return EasingQuintIn(t);
        case EasingTypeQuintOut: return EasingQuintOut(t);
        case EasingTypeQuintInOut: return EasingQuintInOut(t);
        case EasingTypeExpoIn: return EasingExpoIn(t);
        case EasingTypeExpoOut: return EasingExpoOut(t);
        case EasingTypeExpoInOut: return EasingExpoInOut(t);
        case EasingTypeCircIn: return EasingCircIn(t);
        case EasingTypeCircOut: return EasingCircOut(t);
        case EasingTypeCircInOut: return EasingCircInOut(t);
        case EasingTypeBackIn: return EasingBackIn(t);
        case EasingTypeBackOut: return EasingBackOut(t);
        case EasingTypeBackInOut: return EasingBackInOut(t);
        case EasingTypeElasticIn: return EasingElasticIn(t);
        case EasingTypeElasticOut: return EasingElasticOut(t);
        case EasingTypeElasticInOut: return EasingElasticInOut(t);
        case EasingTypeBounceIn: return EasingBounceIn(t);
        case EasingTypeBounceOut: return EasingBounceOut(t);
        case EasingTypeBounceInOut: return EasingBounceInOut(t);
    }

    return 0.f;
}
