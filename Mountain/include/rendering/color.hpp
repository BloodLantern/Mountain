#pragma once

namespace mountain
{
    struct ColorHSV;
    struct Colorf;

    /// @brief The Color struct represents a color in RGBA color space.
    ///        It uses values from 0 to 255 (0xFF). The default alpha value is 255.
    struct Color
    {
        unsigned char r, g, b, a = 0xFF;

        constexpr Color(const unsigned int rgba)
            : r((unsigned char) (rgba >> 24)), g((unsigned char) (rgba >> 16)), b((unsigned char) (rgba >> 8)), a((unsigned char) rgba) {}
        constexpr Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a = 0xFF)
            : r(r), g(g), b(b), a(a) {}

        operator ColorHSV() const;
        operator Colorf() const;
    };

    /// @brief The Colorf struct represents a color in RGBA color space.
    ///        It uses values from 0 to 1. The default alpha value is 1.
    struct Colorf
    {
        float r, g, b, a = 1.f;

        constexpr Colorf(const float r, const float g, const float b, const float a = 1.f)
            : r(r), g(g), b(b), a(a) {}

        operator Color() const;
    };

    Color operator+(const Color c1, const Color c2);
    Color operator*(const Color c1, const Color c2);

    /// @brief The ColorHSV struct represents a color in HSVA color space.
    ///        It uses values from 0 to 255 (0xFF). The default alpha value is 255.
    struct ColorHSV
    {
        unsigned char h, s, v, a = 0xFF;

        constexpr ColorHSV(const unsigned int hsva)
            : h((unsigned char) (hsva >> 24)), s((unsigned char) (hsva >> 16)), v((unsigned char) (hsva >> 8)), a((unsigned char) hsva) {}
        constexpr ColorHSV(const unsigned char h, const unsigned char s, const unsigned char v, const unsigned char a = 0xFF)
            : h(h), s(s), v(v), a(a) {}

        operator Color() const;
    };

    static constexpr Color ColorWhite  = Color(0xFF, 0xFF, 0xFF);
    static constexpr Color ColorGray   = Color(0x7F, 0x7F, 0x7F);
    static constexpr Color ColorBlack  = Color(0x00, 0x00, 0x00);

    static constexpr Color ColorRed    = Color(0xFF, 0x00, 0x00);
    static constexpr Color ColorGreen  = Color(0x00, 0xFF, 0x00);
    static constexpr Color ColorBlue   = Color(0x00, 0x00, 0xFF);

    static constexpr Color ColorYellow = Color(0xFF, 0xFF, 0x00);
    static constexpr Color ColorCyan   = Color(0x00, 0xFF, 0xFF);
    static constexpr Color ColorMagenta = Color(0xFF, 0x00, 0xFF);
}
