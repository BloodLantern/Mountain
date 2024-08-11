#pragma once
#include "Maths/calc.hpp"

BEGIN_MOUNTAIN

static constexpr float_t HueCircle = 1.f; // A circle is 360 degrees, normalized as 1 here
static constexpr float_t HueCircleOver3 = HueCircle / 3.f;
static constexpr float_t HueCircleOver6 = HueCircle / 6.f;

constexpr Color Color::Transparent() { return Color(0.f, 0.f, 0.f, 0.f); }
constexpr Color Color::AliceBlue() { return Color(0xf0 / 255.f, 0xf8 / 255.f, 0xff / 255.f); }
constexpr Color Color::AntiqueWhite() { return Color(0xfa / 255.f, 0xeb / 255.f, 0xd7 / 255.f); }
constexpr Color Color::Aqua() { return Color(0x00 / 255.f, 0xff / 255.f, 0xff / 255.f); }
constexpr Color Color::Aquamarine() { return Color(0x7f / 255.f, 0xff / 255.f, 0xd4 / 255.f); }
constexpr Color Color::Azure() { return Color(0xf0 / 255.f, 0xff / 255.f, 0xff / 255.f); }
constexpr Color Color::Beige() { return Color(0xf5 / 255.f, 0xf5 / 255.f, 0xdc / 255.f); }
constexpr Color Color::Bisque() { return Color(0xff / 255.f, 0xe4 / 255.f, 0xc4 / 255.f); }
constexpr Color Color::Black() { return Color(0.f, 0.f, 0.f); }
constexpr Color Color::BlanchedAlmond() { return Color(0xff / 255.f, 0xeb / 255.f, 0xcd / 255.f); }
constexpr Color Color::Blue() { return Color(0x00 / 255.f, 0x00 / 255.f, 0xff / 255.f); }
constexpr Color Color::BlueViolet() { return Color(0x8a / 255.f, 0x2b / 255.f, 0xe2 / 255.f); }
constexpr Color Color::Brown() { return Color(0xa5 / 255.f, 0x2a / 255.f, 0x2a / 255.f); }
constexpr Color Color::BurlyWood() { return Color(0xde / 255.f, 0xb8 / 255.f, 0x87 / 255.f); }
constexpr Color Color::CadetBlue() { return Color(0x5f / 255.f, 0x9e / 255.f, 0xa0 / 255.f); }
constexpr Color Color::Chartreuse() { return Color(0x7f / 255.f, 0xff / 255.f, 0x00 / 255.f); }
constexpr Color Color::Chocolate() { return Color(0xd2 / 255.f, 0x69 / 255.f, 0x1e / 255.f); }
constexpr Color Color::Coral() { return Color(0xff / 255.f, 0x7f / 255.f, 0x50 / 255.f); }
constexpr Color Color::CornflowerBlue() { return Color(0x64 / 255.f, 0x95 / 255.f, 0xed / 255.f); }
constexpr Color Color::Cornsilk() { return Color(0xff / 255.f, 0xf8 / 255.f, 0xdc / 255.f); }
constexpr Color Color::Crimson() { return Color(0xdc / 255.f, 0x14 / 255.f, 0x3c / 255.f); }
constexpr Color Color::Cyan() { return Color(0x00 / 255.f, 0xff / 255.f, 0xff / 255.f); }
constexpr Color Color::DarkBlue() { return Color(0x00 / 255.f, 0x00 / 255.f, 0x8b / 255.f); }
constexpr Color Color::DarkCyan() { return Color(0x00 / 255.f, 0x8b / 255.f, 0x8b / 255.f); }
constexpr Color Color::DarkGoldenrod() { return Color(0xb8 / 255.f, 0x86 / 255.f, 0x0b / 255.f); }
constexpr Color Color::DarkGray() { return Color(0xa9 / 255.f, 0xa9 / 255.f, 0xa9 / 255.f); }
constexpr Color Color::DarkGreen() { return Color(0x00 / 255.f, 0x64 / 255.f, 0x00 / 255.f); }
constexpr Color Color::DarkKhaki() { return Color(0xbd / 255.f, 0xb7 / 255.f, 0x6b / 255.f); }
constexpr Color Color::DarkMagenta() { return Color(0x8b / 255.f, 0x00 / 255.f, 0x8b / 255.f); }
constexpr Color Color::DarkOliveGreen() { return Color(0x55 / 255.f, 0x6b / 255.f, 0x2f / 255.f); }
constexpr Color Color::DarkOrange() { return Color(0xff / 255.f, 0x8c / 255.f, 0x00 / 255.f); }
constexpr Color Color::DarkOrchid() { return Color(0x99 / 255.f, 0x32 / 255.f, 0xcc / 255.f); }
constexpr Color Color::DarkRed() { return Color(0x8b / 255.f, 0x00 / 255.f, 0x00 / 255.f); }
constexpr Color Color::DarkSalmon() { return Color(0xe9 / 255.f, 0x96 / 255.f, 0x7a / 255.f); }
constexpr Color Color::DarkSeaGreen() { return Color(0x8f / 255.f, 0xbc / 255.f, 0x8b / 255.f); }
constexpr Color Color::DarkSlateBlue() { return Color(0x48 / 255.f, 0x3d / 255.f, 0x8b / 255.f); }
constexpr Color Color::DarkSlateGray() { return Color(0x2f / 255.f, 0x4f / 255.f, 0x4f / 255.f); }
constexpr Color Color::DarkTurquoise() { return Color(0x00 / 255.f, 0xce / 255.f, 0xd1 / 255.f); }
constexpr Color Color::DarkViolet() { return Color(0x94 / 255.f, 0x00 / 255.f, 0xd3 / 255.f); }
constexpr Color Color::DeepPink() { return Color(0xff / 255.f, 0x14 / 255.f, 0x93 / 255.f); }
constexpr Color Color::DeepSkyBlue() { return Color(0x00 / 255.f, 0xbf / 255.f, 0xff / 255.f); }
constexpr Color Color::DimGray() { return Color(0x69 / 255.f, 0x69 / 255.f, 0x69 / 255.f); }
constexpr Color Color::DodgerBlue() { return Color(0x1e / 255.f, 0x90 / 255.f, 0xff / 255.f); }
constexpr Color Color::Firebrick() { return Color(0xb2 / 255.f, 0x22 / 255.f, 0x22 / 255.f); }
constexpr Color Color::FloralWhite() { return Color(0xff / 255.f, 0xfa / 255.f, 0xf0 / 255.f); }
constexpr Color Color::ForestGreen() { return Color(0x22 / 255.f, 0x8b / 255.f, 0x22 / 255.f); }
constexpr Color Color::Fuchsia() { return Color(0xff / 255.f, 0x00 / 255.f, 0xff / 255.f); }
constexpr Color Color::Gainsboro() { return Color(0xdc / 255.f, 0xdc / 255.f, 0xdc / 255.f); }
constexpr Color Color::GhostWhite() { return Color(0xf8 / 255.f, 0xf8 / 255.f, 0xff / 255.f); }
constexpr Color Color::Gold() { return Color(0xff / 255.f, 0xd7 / 255.f, 0x00 / 255.f); }
constexpr Color Color::Goldenrod() { return Color(0xda / 255.f, 0xa5 / 255.f, 0x20 / 255.f); }
constexpr Color Color::Gray() { return Color(0x80 / 255.f, 0x80 / 255.f, 0x80 / 255.f); }
constexpr Color Color::Green() { return Color(0x00 / 255.f, 0x80 / 255.f, 0x00 / 255.f); }
constexpr Color Color::GreenYellow() { return Color(0xad / 255.f, 0xff / 255.f, 0x2f / 255.f); }
constexpr Color Color::Honeydew() { return Color(0xf0 / 255.f, 0xff / 255.f, 0xf0 / 255.f); }
constexpr Color Color::HotPink() { return Color(0xff / 255.f, 0x69 / 255.f, 0xb4 / 255.f); }
constexpr Color Color::IndianRed() { return Color(0xcd / 255.f, 0x5c / 255.f, 0x5c / 255.f); }
constexpr Color Color::Indigo() { return Color(0x4b / 255.f, 0x00 / 255.f, 0x82 / 255.f); }
constexpr Color Color::Ivory() { return Color(0xff / 255.f, 0xff / 255.f, 0xf0 / 255.f); }
constexpr Color Color::Khaki() { return Color(0xf0 / 255.f, 0xe6 / 255.f, 0x8c / 255.f); }
constexpr Color Color::Lavender() { return Color(0xe6 / 255.f, 0xe6 / 255.f, 0xfa / 255.f); }
constexpr Color Color::LavenderBlush() { return Color(0xff / 255.f, 0xf0 / 255.f, 0xf5 / 255.f); }
constexpr Color Color::LawnGreen() { return Color(0x7c / 255.f, 0xfc / 255.f, 0x00 / 255.f); }
constexpr Color Color::LemonChiffon() { return Color(0xff / 255.f, 0xfa / 255.f, 0xcd / 255.f); }
constexpr Color Color::LightBlue() { return Color(0xad / 255.f, 0xd8 / 255.f, 0xe6 / 255.f); }
constexpr Color Color::LightCoral() { return Color(0xf0 / 255.f, 0x80 / 255.f, 0x80 / 255.f); }
constexpr Color Color::LightCyan() { return Color(0xe0 / 255.f, 0xff / 255.f, 0xff / 255.f); }
constexpr Color Color::LightGoldenrodYellow() { return Color(0xfa / 255.f, 0xfa / 255.f, 0xd2 / 255.f); }
constexpr Color Color::LightGray() { return Color(0xd3 / 255.f, 0xd3 / 255.f, 0xd3 / 255.f); }
constexpr Color Color::LightGreen() { return Color(0x90 / 255.f, 0xee / 255.f, 0x90 / 255.f); }
constexpr Color Color::LightPink() { return Color(0xff / 255.f, 0xb6 / 255.f, 0xc1 / 255.f); }
constexpr Color Color::LightSalmon() { return Color(0xff / 255.f, 0xa0 / 255.f, 0x7a / 255.f); }
constexpr Color Color::LightSeaGreen() { return Color(0x20 / 255.f, 0xb2 / 255.f, 0xaa / 255.f); }
constexpr Color Color::LightSkyBlue() { return Color(0x87 / 255.f, 0xce / 255.f, 0xfa / 255.f); }
constexpr Color Color::LightSlateGray() { return Color(0x77 / 255.f, 0x88 / 255.f, 0x99 / 255.f); }
constexpr Color Color::LightSteelBlue() { return Color(0xb0 / 255.f, 0xc4 / 255.f, 0xde / 255.f); }
constexpr Color Color::LightYellow() { return Color(0xff / 255.f, 0xff / 255.f, 0xe0 / 255.f); }
constexpr Color Color::Lime() { return Color(0x00 / 255.f, 0xff / 255.f, 0x00 / 255.f); }
constexpr Color Color::LimeGreen() { return Color(0x32 / 255.f, 0xcd / 255.f, 0x32 / 255.f); }
constexpr Color Color::Linen() { return Color(0xfa / 255.f, 0xf0 / 255.f, 0xe6 / 255.f); }
constexpr Color Color::Magenta() { return Color(0xff / 255.f, 0x00 / 255.f, 0xff / 255.f); }
constexpr Color Color::Maroon() { return Color(0x80 / 255.f, 0x00 / 255.f, 0x00 / 255.f); }
constexpr Color Color::MediumAquamarine() { return Color(0x66 / 255.f, 0xcd / 255.f, 0xaa / 255.f); }
constexpr Color Color::MediumBlue() { return Color(0x00 / 255.f, 0x00 / 255.f, 0xcd / 255.f); }
constexpr Color Color::MediumOrchid() { return Color(0xba / 255.f, 0x55 / 255.f, 0xd3 / 255.f); }
constexpr Color Color::MediumPurple() { return Color(0x93 / 255.f, 0x70 / 255.f, 0xdb / 255.f); }
constexpr Color Color::MediumSeaGreen() { return Color(0x3c / 255.f, 0xb3 / 255.f, 0x71 / 255.f); }
constexpr Color Color::MediumSlateBlue() { return Color(0x7b / 255.f, 0x68 / 255.f, 0xee / 255.f); }
constexpr Color Color::MediumSpringGreen() { return Color(0x00 / 255.f, 0xfa / 255.f, 0x9a / 255.f); }
constexpr Color Color::MediumTurquoise() { return Color(0x48 / 255.f, 0xd1 / 255.f, 0xcc / 255.f); }
constexpr Color Color::MediumVioletRed() { return Color(0xc7 / 255.f, 0x15 / 255.f, 0x85 / 255.f); }
constexpr Color Color::MidnightBlue() { return Color(0x19 / 255.f, 0x19 / 255.f, 0x70 / 255.f); }
constexpr Color Color::MintCream() { return Color(0xf5 / 255.f, 0xff / 255.f, 0xfa / 255.f); }
constexpr Color Color::MistyRose() { return Color(0xff / 255.f, 0xe4 / 255.f, 0xe1 / 255.f); }
constexpr Color Color::Moccasin() { return Color(0xff / 255.f, 0xe4 / 255.f, 0xb5 / 255.f); }
constexpr Color Color::MonoGameOrange() { return Color(0xe7 / 255.f, 0x3c / 255.f, 0x00 / 255.f); }
constexpr Color Color::NavajoWhite() { return Color(0xff / 255.f, 0xde / 255.f, 0xad / 255.f); }
constexpr Color Color::Navy() { return Color(0x00 / 255.f, 0x00 / 255.f, 0x80 / 255.f); }
constexpr Color Color::OldLace() { return Color(0xfd / 255.f, 0xf5 / 255.f, 0xe6 / 255.f); }
constexpr Color Color::Olive() { return Color(0x80 / 255.f, 0x80 / 255.f, 0x00 / 255.f); }
constexpr Color Color::OliveDrab() { return Color(0x6b / 255.f, 0x8e / 255.f, 0x23 / 255.f); }
constexpr Color Color::Orange() { return Color(0xff / 255.f, 0xa5 / 255.f, 0x00 / 255.f); }
constexpr Color Color::OrangeRed() { return Color(0xff / 255.f, 0x45 / 255.f, 0x00 / 255.f); }
constexpr Color Color::Orchid() { return Color(0xda / 255.f, 0x70 / 255.f, 0xd6 / 255.f); }
constexpr Color Color::PaleGoldenrod() { return Color(0xee / 255.f, 0xe8 / 255.f, 0xaa / 255.f); }
constexpr Color Color::PaleGreen() { return Color(0x98 / 255.f, 0xfb / 255.f, 0x98 / 255.f); }
constexpr Color Color::PaleTurquoise() { return Color(0xaf / 255.f, 0xee / 255.f, 0xee / 255.f); }
constexpr Color Color::PaleVioletRed() { return Color(0xdb / 255.f, 0x70 / 255.f, 0x93 / 255.f); }
constexpr Color Color::PapayaWhip() { return Color(0xff / 255.f, 0xef / 255.f, 0xd5 / 255.f); }
constexpr Color Color::PeachPuff() { return Color(0xff / 255.f, 0xda / 255.f, 0xb9 / 255.f); }
constexpr Color Color::Peru() { return Color(0xcd / 255.f, 0x85 / 255.f, 0x3f / 255.f); }
constexpr Color Color::Pink() { return Color(0xff / 255.f, 0xc0 / 255.f, 0xcb / 255.f); }
constexpr Color Color::Plum() { return Color(0xdd / 255.f, 0xa0 / 255.f, 0xdd / 255.f); }
constexpr Color Color::PowderBlue() { return Color(0xb0 / 255.f, 0xe0 / 255.f, 0xe6 / 255.f); }
constexpr Color Color::Purple() { return Color(0x80 / 255.f, 0x00 / 255.f, 0x80 / 255.f); }
constexpr Color Color::Red() { return Color(0xff / 255.f, 0x00 / 255.f, 0x00 / 255.f); }
constexpr Color Color::RosyBrown() { return Color(0xbc / 255.f, 0x8f / 255.f, 0x8f / 255.f); }
constexpr Color Color::RoyalBlue() { return Color(0x41 / 255.f, 0x69 / 255.f, 0xe1 / 255.f); }
constexpr Color Color::SaddleBrown() { return Color(0x8b / 255.f, 0x45 / 255.f, 0x13 / 255.f); }
constexpr Color Color::Salmon() { return Color(0xfa / 255.f, 0x80 / 255.f, 0x72 / 255.f); }
constexpr Color Color::SandyBrown() { return Color(0xf4 / 255.f, 0xa4 / 255.f, 0x60 / 255.f); }
constexpr Color Color::SeaGreen() { return Color(0x2e / 255.f, 0x8b / 255.f, 0x57 / 255.f); }
constexpr Color Color::SeaShell() { return Color(0xff / 255.f, 0xf5 / 255.f, 0xee / 255.f); }
constexpr Color Color::Sienna() { return Color(0xa0 / 255.f, 0x52 / 255.f, 0x2d / 255.f); }
constexpr Color Color::Silver() { return Color(0xc0 / 255.f, 0xc0 / 255.f, 0xc0 / 255.f); }
constexpr Color Color::SkyBlue() { return Color(0x87 / 255.f, 0xce / 255.f, 0xeb / 255.f); }
constexpr Color Color::SlateBlue() { return Color(0x6a / 255.f, 0x5a / 255.f, 0xcd / 255.f); }
constexpr Color Color::SlateGray() { return Color(0x70 / 255.f, 0x80 / 255.f, 0x90 / 255.f); }
constexpr Color Color::Snow() { return Color(0xff / 255.f, 0xfa / 255.f, 0xfa / 255.f); }
constexpr Color Color::SpringGreen() { return Color(0x00 / 255.f, 0xff / 255.f, 0x7f / 255.f); }
constexpr Color Color::SteelBlue() { return Color(0x46 / 255.f, 0x82 / 255.f, 0xb4 / 255.f); }
constexpr Color Color::Tan() { return Color(0xd2 / 255.f, 0xb4 / 255.f, 0x8c / 255.f); }
constexpr Color Color::Teal() { return Color(0x00 / 255.f, 0x80 / 255.f, 0x80 / 255.f); }
constexpr Color Color::Thistle() { return Color(0xd8 / 255.f, 0xbf / 255.f, 0xd8 / 255.f); }
constexpr Color Color::Tomato() { return Color(0xff / 255.f, 0x63 / 255.f, 0x47 / 255.f); }
constexpr Color Color::Turquoise() { return Color(0x40 / 255.f, 0xe0 / 255.f, 0xd0 / 255.f); }
constexpr Color Color::Violet() { return Color(0xee / 255.f, 0x82 / 255.f, 0xee / 255.f); }
constexpr Color Color::Wheat() { return Color(0xf5 / 255.f, 0xde / 255.f, 0xb3 / 255.f); }
constexpr Color Color::White() { return Color(1.f, 1.f, 1.f); }
constexpr Color Color::WhiteSmoke() { return Color(0xf5 / 255.f, 0xf5 / 255.f, 0xf5 / 255.f); }
constexpr Color Color::Yellow() { return Color(0xff / 255.f, 0xff / 255.f, 0x00 / 255.f); }
constexpr Color Color::YellowGreen() { return Color(0x9a / 255.f, 0xcd / 255.f, 0x32 / 255.f); }

constexpr float_t* Color::Data() { return &r; }

constexpr const float_t* Color::Data() const { return &r; }

constexpr Color::operator ColorHsva() const
{
    ColorHsva hsv = { 0.f, 0.f, 0.f, a };
    const float_t minVal = std::min(std::min(r, g), b);
    const float_t maxVal = std::max(std::max(r, g), b);
    hsv.v = maxVal;
    const float_t delta = maxVal - minVal;
    
    if (Calc::IsZero(delta)) // Black
    {
        hsv.h = 0.f;
        hsv.s = 0.f;
    }
    else
    {
        hsv.s = delta / maxVal;
        const float_t deltaInverse = 1.f / delta;
        if (Calc::Equals(r, maxVal))
            hsv.h = HueCircleOver3 * 0 + HueCircleOver6 * (g - b) * deltaInverse;
        else if (Calc::Equals(g, maxVal))
            hsv.h = HueCircleOver3 * 1 + HueCircleOver6 * (b - r) * deltaInverse;
        else
            hsv.h = HueCircleOver3 * 2 + HueCircleOver6 * (r - g) * deltaInverse;

        const float_t floor = Calc::Floor(hsv.h);
        if (hsv.h < 0.f)
            hsv.h += Calc::Abs(floor);
        else
            hsv.h -= floor;
    }
    return hsv;
}

constexpr Color::operator Vector3() const { return Vector3(r, g, b); }

constexpr Color::operator Vector4() const { return Vector4(r, g, b, a); }

constexpr ColorHsva ColorHsva::White() { return ColorHsva(0.f, 0.f, 1.f); }

constexpr ColorHsva ColorHsva::Gray() { return ColorHsva(0.f, 0.f, 0.5f); }

constexpr ColorHsva ColorHsva::Black() { return ColorHsva(0.f, 0.f, 0.f); }

constexpr ColorHsva ColorHsva::Red() { return ColorHsva(0.f, 1.f, 1.f); }

constexpr ColorHsva ColorHsva::Green() { return ColorHsva(HueCircleOver3, 1.f, 1.f); }

constexpr ColorHsva ColorHsva::Blue() { return ColorHsva(HueCircleOver3 * 2, 1.f, 1.f); }

constexpr ColorHsva ColorHsva::Yellow() { return ColorHsva(HueCircleOver6, 1.f, 1.f); }

constexpr ColorHsva ColorHsva::LightBlue() { return ColorHsva(HueCircleOver3 + HueCircleOver6, 1.f, 1.f); }

constexpr ColorHsva ColorHsva::Magenta() { return ColorHsva(HueCircleOver3 * 2 + HueCircleOver6, 1.f, 1.f); }

constexpr ColorHsva::operator Color() const
{
    if (Calc::IsZero(s)) // Grayscale
        return { v, v, v, a };
    
    const uint8_t hi = static_cast<uint8_t>(h / HueCircleOver6);
    const float_t f = Calc::Modulo(h, HueCircleOver6) * 6.f;
    const float_t p = v * (1.f - s);
    const float_t q = v * (1.f - s * f);
    const float_t t = v * (1.f - s * (1.f - f));

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

constexpr ColorHsva::operator Vector3() const { return Vector3(h, s, v); }

constexpr ColorHsva::operator Vector4() const { return Vector4(h, s, v, a); }

constexpr Color operator+(const Color& c1, const Color& c2) { return Color(std::min(c1.r + c2.r, 1.f), std::min(c1.g + c2.g, 1.f), std::min(c1.b + c2.b, 1.f), std::min(c1.a + c2.a, 1.f)); }

constexpr Color operator*(const Color& c1, const Color& c2) { return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a); }

constexpr Color operator*(const Color color, const float_t alphaFactor) { return Color(color.r, color.g, color.b, color.a * alphaFactor); }

constexpr bool_t operator==(const Color& c1, const Color& c2) { return Calc::Equals(c1.r, c2.r) && Calc::Equals(c1.g, c2.g) && Calc::Equals(c1.b, c2.b) && Calc::Equals(c1.a, c2.a); }

constexpr bool_t operator!=(const Color& c1, const Color& c2) { return !(c1 == c2); }

constexpr ColorHsva operator*(const ColorHsva& color, const float_t alphaFactor) { return ColorHsva(color.h, color.s, color.v, std::clamp(color.a * alphaFactor, 0.f, 1.f)); }

constexpr bool_t operator==(const ColorHsva& c1, const ColorHsva& c2) { return Calc::Equals(c1.h, c2.h) && Calc::Equals(c1.s, c2.s) && Calc::Equals(c1.v, c2.v) && Calc::Equals(c1.a, c2.a); }

constexpr bool_t operator!=(const ColorHsva& c1, const ColorHsva& c2) { return !(c1 == c2); }

END_MOUNTAIN
