#include "color.hpp"

#include <cmath>

#define HUE_ANGLE 43

mountain::Color::operator mountain::ColorHSV() const
{
    ColorHSV hsv = { 0, 0, 0, a };
    unsigned char minVal = std::min(std::min(r, g), b);
    unsigned char maxVal = std::max(std::max(r, g), b);
    hsv.v = maxVal;
    unsigned char delta = maxVal - minVal;
    if (delta == 0)
    {
        hsv.h = 0;
        hsv.s = 0;
    }
    else
    {
        hsv.s = 0xFF * delta / maxVal;
        if (r == maxVal)
        {
            hsv.h = 0 + HUE_ANGLE * (g - b) / delta;
        }
        else if (g == maxVal)
        {
            hsv.h = 85 + HUE_ANGLE * (b - r) / delta;
        }
        else
        {
            hsv.h = 171 + HUE_ANGLE * (r - g) / delta;
        }
    }
    return hsv;
}

mountain::ColorHSV::operator mountain::Color() const
{
    unsigned char hi = h / HUE_ANGLE;
    unsigned char f = h % HUE_ANGLE * 6;
    unsigned char p = (v * (0xFF - s) + 0x7F) / 0xFF;
    unsigned char q = (v * (0xFF - (s * f + 0x7F) / 0xFF) + 0x7F) / 0xFF;
    unsigned char t = (v * (0xFF - (s * (0xFF - f) + 0x7F) / 0xFF) + 0x7F) / 0xFF;

    switch (hi)
    {
    case 0:
        return { v, t, p, a };
    case 1:
        return { q, v, p, a };
    case 2:
        return { p, v, t, a };
    case 3:
        return { p, q, v, a };
    case 4:
        return { t, p, v, a };
    default:
        return { v, p, q, a };
    }
}

mountain::Color mountain::operator+(const Color c1, const Color c2)
{
    return Color(
        c1.r + c2.r > 0xFF ? 0xFF : c1.r + c2.r,
        c1.g + c2.g > 0xFF ? 0xFF : c1.g + c2.g,
        c1.b + c2.b > 0xFF ? 0xFF : c1.b + c2.b,
        c1.a + c2.a > 0xFF ? 0xFF : c1.a + c2.a
    );
}

mountain::Color mountain::operator*(const Color c1, const Color c2)
{
    return Color(
        c1.r * c2.r > 0xFF ? 0xFF : c1.r * c2.r,
        c1.g * c2.g > 0xFF ? 0xFF : c1.g * c2.g,
        c1.b * c2.b > 0xFF ? 0xFF : c1.b * c2.b,
        c1.a * c2.a > 0xFF ? 0xFF : c1.a * c2.a
    );
}
