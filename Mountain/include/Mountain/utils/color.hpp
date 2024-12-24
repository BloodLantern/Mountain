#pragma once

#include <format>
#include <sstream>

#include <Maths/easing.hpp>
#include <Maths/vector3.hpp>
#include <Maths/vector4.hpp>

#include "Mountain/core.hpp"

// Undef windows min and max macros in case they were defined
#undef min
#undef max

/// @file color.hpp
/// @brief Defines multiple color structs.

namespace Mountain
{
    struct ColorHsva;

    /// @brief The Color struct represents a color in RGBA color space.
    ///
    /// It uses @c float values from 0 to 1. The default alpha value is 1.
    struct MOUNTAIN_API Color
    {
        // Constants taken from https://github.com/MonoGame/MonoGame/blob/develop/MonoGame.Framework/Color.cs

        /// @brief Constant for Transparent.
        /// @return The Transparent color.
        static constexpr Color Transparent();

        /// @brief Constant for Alice Blue.
        /// @return The Alice Blue color.
        static constexpr Color AliceBlue();

        /// @brief Constant for Antique White.
        /// @return The Antique White color.
        static constexpr Color AntiqueWhite();

        /// @brief Constant for Aqua.
        /// @return The Aqua color.
        static constexpr Color Aqua();

        /// @brief Constant for Aquamarine.
        /// @return The Aquamarine color.
        static constexpr Color Aquamarine();

        /// @brief Constant for Azure.
        /// @return The Azure color.
        static constexpr Color Azure();

        /// @brief Constant for Beige.
        /// @return The Beige color.
        static constexpr Color Beige();

        /// @brief Constant for Bisque.
        /// @return The Bisque color.
        static constexpr Color Bisque();

        /// @brief Constant for Black.
        /// @return The Black color.
        static constexpr Color Black();

        /// @brief Constant for Blanched Almond.
        /// @return The Blanched Almond color.
        static constexpr Color BlanchedAlmond();

        /// @brief Constant for Blue.
        /// @return The Blue color.
        static constexpr Color Blue();

        /// @brief Constant for Blue Violet.
        /// @return The Blue Violet color.
        static constexpr Color BlueViolet();

        /// @brief Constant for Brown.
        /// @return The Brown color.
        static constexpr Color Brown();

        /// @brief Constant for Burly Wood.
        /// @return The Burly Wood color.
        static constexpr Color BurlyWood();

        /// @brief Constant for Cadet Blue.
        /// @return The Cadet Blue color.
        static constexpr Color CadetBlue();

        /// @brief Constant for Chartreuse.
        /// @return The Chartreuse color.
        static constexpr Color Chartreuse();

        /// @brief Constant for Chocolate.
        /// @return The Chocolate color.
        static constexpr Color Chocolate();

        /// @brief Constant for Coral.
        /// @return The Coral color.
        static constexpr Color Coral();

        /// @brief Constant for Cornflower Blue.
        /// @return The Cornflower Blue color.
        static constexpr Color CornflowerBlue();

        /// @brief Constant for Cornsilk.
        /// @return The Cornsilk color.
        static constexpr Color Cornsilk();

        /// @brief Constant for Crimson.
        /// @return The Crimson color.
        static constexpr Color Crimson();

        /// @brief Constant for Cyan.
        /// @return The Cyan color.
        static constexpr Color Cyan();

        /// @brief Constant for Dark Blue.
        /// @return The Dark Blue color.
        static constexpr Color DarkBlue();

        /// @brief Constant for Dark Cyan.
        /// @return The Dark Cyan color.
        static constexpr Color DarkCyan();

        /// @brief Constant for Dark Goldenrod.
        /// @return The Dark Goldenrod color.
        static constexpr Color DarkGoldenrod();

        /// @brief Constant for Dark Gray.
        /// @return The Dark Gray color.
        static constexpr Color DarkGray();

        /// @brief Constant for Dark Green.
        /// @return The Dark Green color.
        static constexpr Color DarkGreen();

        /// @brief Constant for Dark Khaki.
        /// @return The Dark Khaki color.
        static constexpr Color DarkKhaki();

        /// @brief Constant for Dark Magenta.
        /// @return The Dark Magenta color.
        static constexpr Color DarkMagenta();

        /// @brief Constant for Dark Olive Green.
        /// @return The Dark Olive Green color.
        static constexpr Color DarkOliveGreen();

        /// @brief Constant for Dark Orange.
        /// @return The Dark Orange color.
        static constexpr Color DarkOrange();

        /// @brief Constant for Dark Orchid.
        /// @return The Dark Orchid color.
        static constexpr Color DarkOrchid();

        /// @brief Constant for Dark Red.
        /// @return The Dark Red color.
        static constexpr Color DarkRed();

        /// @brief Constant for Dark Salmon.
        /// @return The Dark Salmon color.
        static constexpr Color DarkSalmon();

        /// @brief Constant for Dark Sea Green.
        /// @return The Dark Sea Green color.
        static constexpr Color DarkSeaGreen();

        /// @brief Constant for Dark Slate Blue.
        /// @return The Dark Slate Blue color.
        static constexpr Color DarkSlateBlue();

        /// @brief Constant for Dark Slate Gray.
        /// @return The Dark Slate Gray color.
        static constexpr Color DarkSlateGray();

        /// @brief Constant for Dark Turquoise.
        /// @return The Dark Turquoise color.
        static constexpr Color DarkTurquoise();

        /// @brief Constant for Dark Violet.
        /// @return The Dark Violet color.
        static constexpr Color DarkViolet();

        /// @brief Constant for Deep Pink.
        /// @return The Deep Pink color.
        static constexpr Color DeepPink();

        /// @brief Constant for Deep Sky Blue.
        /// @return The Deep Sky Blue color.
        static constexpr Color DeepSkyBlue();

        /// @brief Constant for Dim Gray.
        /// @return The Dim Gray color.
        static constexpr Color DimGray();

        /// @brief Constant for Dodger Blue.
        /// @return The Dodger Blue color.
        static constexpr Color DodgerBlue();

        /// @brief Constant for Firebrick.
        /// @return The Firebrick color.
        static constexpr Color Firebrick();

        /// @brief Constant for Floral White.
        /// @return The Floral White color.
        static constexpr Color FloralWhite();

        /// @brief Constant for Forest Green.
        /// @return The Forest Green color.
        static constexpr Color ForestGreen();

        /// @brief Constant for Fuchsia.
        /// @return The Fuchsia color.
        static constexpr Color Fuchsia();

        /// @brief Constant for Gainsboro.
        /// @return The Gainsboro color.
        static constexpr Color Gainsboro();

        /// @brief Constant for Ghost White.
        /// @return The Ghost White color.
        static constexpr Color GhostWhite();

        /// @brief Constant for Gold.
        /// @return The Gold color.
        static constexpr Color Gold();

        /// @brief Constant for Goldenrod.
        /// @return The Goldenrod color.
        static constexpr Color Goldenrod();

        /// @brief Constant for Gray.
        /// @return The Gray color.
        static constexpr Color Gray();

        /// @brief Constant for Green.
        /// @return The Green color.
        static constexpr Color Green();

        /// @brief Constant for Green Yellow.
        /// @return The Green Yellow color.
        static constexpr Color GreenYellow();

        /// @brief Constant for Honeydew.
        /// @return The Honeydew color.
        static constexpr Color Honeydew();

        /// @brief Constant for Hot Pink.
        /// @return The Hot Pink color.
        static constexpr Color HotPink();

        /// @brief Constant for Indian Red.
        /// @return The Indian Red color.
        static constexpr Color IndianRed();

        /// @brief Constant for Indigo.
        /// @return The Indigo color.
        static constexpr Color Indigo();

        /// @brief Constant for Ivory.
        /// @return The Ivory color.
        static constexpr Color Ivory();

        /// @brief Constant for Khaki.
        /// @return The Khaki color.
        static constexpr Color Khaki();

        /// @brief Constant for Lavender.
        /// @return The Lavender color.
        static constexpr Color Lavender();

        /// @brief Constant for Lavender Blush.
        /// @return The Lavender Blush color.
        static constexpr Color LavenderBlush();

        /// @brief Constant for Lawn Green.
        /// @return The Lawn Green color.
        static constexpr Color LawnGreen();

        /// @brief Constant for Lemon Chiffon.
        /// @return The Lemon Chiffon color.
        static constexpr Color LemonChiffon();

        /// @brief Constant for Light Blue.
        /// @return The Light Blue color.
        static constexpr Color LightBlue();

        /// @brief Constant for Light Coral.
        /// @return The Light Coral color.
        static constexpr Color LightCoral();

        /// @brief Constant for Light Cyan.
        /// @return The Light Cyan color.
        static constexpr Color LightCyan();

        /// @brief Constant for Light Goldenrod Yellow.
        /// @return The Light Goldenrod Yellow color.
        static constexpr Color LightGoldenrodYellow();

        /// @brief Constant for Light Gray.
        /// @return The Light Gray color.
        static constexpr Color LightGray();

        /// @brief Constant for Light Green.
        /// @return The Light Green color.
        static constexpr Color LightGreen();

        /// @brief Constant for Light Pink.
        /// @return The Light Pink color.
        static constexpr Color LightPink();

        /// @brief Constant for Light Salmon.
        /// @return The Light Salmon color.
        static constexpr Color LightSalmon();

        /// @brief Constant for Light Sea Green.
        /// @return The Light Sea Green color.
        static constexpr Color LightSeaGreen();

        /// @brief Constant for Light Sky Blue.
        /// @return The Light Sky Blue color.
        static constexpr Color LightSkyBlue();

        /// @brief Constant for Light Slate Gray.
        /// @return The Light Slate Gray color.
        static constexpr Color LightSlateGray();

        /// @brief Constant for Light Steel Blue.
        /// @return The Light Steel Blue color.
        static constexpr Color LightSteelBlue();

        /// @brief Constant for Light Yellow.
        /// @return The Light Yellow color.
        static constexpr Color LightYellow();

        /// @brief Constant for Lime.
        /// @return The Lime color.
        static constexpr Color Lime();

        /// @brief Constant for Lime Green.
        /// @return The Lime Green color.
        static constexpr Color LimeGreen();

        /// @brief Constant for Linen.
        /// @return The Linen color.
        static constexpr Color Linen();

        /// @brief Constant for Magenta.
        /// @return The Magenta color.
        static constexpr Color Magenta();

        /// @brief Constant for Maroon.
        /// @return The Maroon color.
        static constexpr Color Maroon();

        /// @brief Constant for Medium Aquamarine.
        /// @return The Medium Aquamarine color.
        static constexpr Color MediumAquamarine();

        /// @brief Constant for Medium Blue.
        /// @return The Medium Blue color.
        static constexpr Color MediumBlue();

        /// @brief Constant for Medium Orchid.
        /// @return The Medium Orchid color.
        static constexpr Color MediumOrchid();

        /// @brief Constant for Medium Purple.
        /// @return The Medium Purple color.
        static constexpr Color MediumPurple();

        /// @brief Constant for Medium Sea Green.
        /// @return The Medium Sea Green color.
        static constexpr Color MediumSeaGreen();

        /// @brief Constant for Medium Slate Blue.
        /// @return The Medium Slate Blue color.
        static constexpr Color MediumSlateBlue();

        /// @brief Constant for Medium Spring Green.
        /// @return The Medium Spring Green color.
        static constexpr Color MediumSpringGreen();

        /// @brief Constant for Medium Turquoise.
        /// @return The Medium Turquoise color.
        static constexpr Color MediumTurquoise();

        /// @brief Constant for Medium Violet Red.
        /// @return The Medium Violet Red color.
        static constexpr Color MediumVioletRed();

        /// @brief Constant for Midnight Blue.
        /// @return The Midnight Blue color.
        static constexpr Color MidnightBlue();

        /// @brief Constant for Mint Cream.
        /// @return The Mint Cream color.
        static constexpr Color MintCream();

        /// @brief Constant for Misty Rose.
        /// @return The Misty Rose color.
        static constexpr Color MistyRose();

        /// @brief Constant for Moccasin.
        /// @return The Moccasin color.
        static constexpr Color Moccasin();

        /// @brief Constant for MonoGame Orange.
        /// @return The MonoGame Orange color.
        static constexpr Color MonoGameOrange();

        /// @brief Constant for Navajo White.
        /// @return The Navajo White color.
        static constexpr Color NavajoWhite();

        /// @brief Constant for Navy.
        /// @return The Navy color.
        static constexpr Color Navy();

        /// @brief Constant for Old Lace.
        /// @return The Old Lace color.
        static constexpr Color OldLace();

        /// @brief Constant for Olive.
        /// @return The Olive color.
        static constexpr Color Olive();

        /// @brief Constant for Olive Drab.
        /// @return The Olive Drab color.
        static constexpr Color OliveDrab();

        /// @brief Constant for Orange.
        /// @return The Orange color.
        static constexpr Color Orange();

        /// @brief Constant for Orange Red.
        /// @return The Orange Red color.
        static constexpr Color OrangeRed();

        /// @brief Constant for Orchid.
        /// @return The Orchid color.
        static constexpr Color Orchid();

        /// @brief Constant for Pale Goldenrod.
        /// @return The Pale Goldenrod color.
        static constexpr Color PaleGoldenrod();

        /// @brief Constant for Pale Green.
        /// @return The Pale Green color.
        static constexpr Color PaleGreen();

        /// @brief Constant for Pale Turquoise.
        /// @return The Pale Turquoise color.
        static constexpr Color PaleTurquoise();

        /// @brief Constant for Pale Violet Red.
        /// @return The Pale Violet Red color.
        static constexpr Color PaleVioletRed();

        /// @brief Constant for Papaya Whip.
        /// @return The Papaya Whip color.
        static constexpr Color PapayaWhip();

        /// @brief Constant for Peach Puff.
        /// @return The Peach Puff color.
        static constexpr Color PeachPuff();

        /// @brief Constant for Peru.
        /// @return The Peru color.
        static constexpr Color Peru();

        /// @brief Constant for Pink.
        /// @return The Pink color.
        static constexpr Color Pink();

        /// @brief Constant for Plum.
        /// @return The Plum color.
        static constexpr Color Plum();

        /// @brief Constant for Powder Blue.
        /// @return The Powder Blue color.
        static constexpr Color PowderBlue();

        /// @brief Constant for Purple.
        /// @return The Purple color.
        static constexpr Color Purple();

        /// @brief Constant for Red.
        /// @return The Red color.
        static constexpr Color Red();

        /// @brief Constant for Rosy Brown.
        /// @return The Rosy Brown color.
        static constexpr Color RosyBrown();

        /// @brief Constant for Royal Blue.
        /// @return The Royal Blue color.
        static constexpr Color RoyalBlue();

        /// @brief Constant for Saddle Brown.
        /// @return The Saddle Brown color.
        static constexpr Color SaddleBrown();

        /// @brief Constant for Salmon.
        /// @return The Salmon color.
        static constexpr Color Salmon();

        /// @brief Constant for Sandy Brown.
        /// @return The Sandy Brown color.
        static constexpr Color SandyBrown();

        /// @brief Constant for Sea Green.
        /// @return The Sea Green color.
        static constexpr Color SeaGreen();

        /// @brief Constant for SeaShell.
        /// @return The SeaShell color.
        static constexpr Color SeaShell();

        /// @brief Constant for Sienna.
        /// @return The Sienna color.
        static constexpr Color Sienna();

        /// @brief Constant for Silver.
        /// @return The Silver color.
        static constexpr Color Silver();

        /// @brief Constant for Sky Blue.
        /// @return The Sky Blue color.
        static constexpr Color SkyBlue();

        /// @brief Constant for Slate Blue.
        /// @return The Slate Blue color.
        static constexpr Color SlateBlue();

        /// @brief Constant for Slate Gray.
        /// @return The Slate Gray color.
        static constexpr Color SlateGray();

        /// @brief Constant for Snow.
        /// @return The Snow color.
        static constexpr Color Snow();

        /// @brief Constant for Spring Green.
        /// @return The Spring Green color.
        static constexpr Color SpringGreen();

        /// @brief Constant for Steel Blue.
        /// @return The Steel Blue color.
        static constexpr Color SteelBlue();

        /// @brief Constant for Tan.
        /// @return The Tan color.
        static constexpr Color Tan();

        /// @brief Constant for Teal.
        /// @return The Teal color.
        static constexpr Color Teal();

        /// @brief Constant for Thistle.
        /// @return The Thistle color.
        static constexpr Color Thistle();

        /// @brief Constant for Tomato.
        /// @return The Tomato color.
        static constexpr Color Tomato();

        /// @brief Constant for Turquoise.
        /// @return The Turquoise color.
        static constexpr Color Turquoise();

        /// @brief Constant for Violet.
        /// @return The Violet color.
        static constexpr Color Violet();

        /// @brief Constant for Wheat.
        /// @return The Wheat color.
        static constexpr Color Wheat();

        /// @brief Constant for White.
        /// @return The White color.
        static constexpr Color White();

        /// @brief Constant for White Smoke.
        /// @return The White Smoke color.
        static constexpr Color WhiteSmoke();

        /// @brief Constant for Yellow.
        /// @return The Yellow color.
        static constexpr Color Yellow();

        /// @brief Constant for Yellow Green.
        /// @return The Yellow Green color.
        static constexpr Color YellowGreen();

        /// @brief Red component
        float_t r = 0.f;
        /// @brief Green component
        float_t g = 0.f;
        /// @brief Blue component
        float_t b = 0.f;
        /// @brief Alpha component
        float_t a = 1.f;

        [[nodiscard]]
        Color() = default;

        /// @brief Constructs a grayscale color with each component equal to @p rgb
        ///
        /// @param rgb Red, Green and Blue components
        /// @param a Alpha component
        [[nodiscard]]
        explicit constexpr Color(const float_t rgb, const float_t a = 1.f)
        : r(rgb), g(rgb), b(rgb), a(a) {}

        /// @brief Constructs a color with each specified component
        ///
        /// @param r Red component
        /// @param g Green component
        /// @param b Blue component
        /// @param a Alpha component
        [[nodiscard]]
        constexpr Color(const float_t r, const float_t g, const float_t b, const float_t a = 1.f)
        : r(r), g(g), b(b), a(a) {}

        /// @brief Constructs a color from a Vector3 and an alpha value
        ///
        /// @param rgb Red, Green and Blue components
        /// @param a Alpha component
        [[nodiscard]]
        explicit constexpr Color(const Vector3& rgb, const float_t a = 1.f)
        : r(rgb.x), g(rgb.y), b(rgb.z), a(a) {}

        /// @brief Constructs a color from a Vector4
        ///
        /// @param rgba Color components
        [[nodiscard]]
        explicit constexpr Color(const Vector4& rgba)
        : r(rgba.x), g(rgba.y), b(rgba.z), a(rgba.w) {}

        [[nodiscard]]
        uint32_t GetPackedValue() const;

        [[nodiscard]]
        constexpr float_t* Data();

        [[nodiscard]]
        constexpr const float_t* Data() const;

        /// @brief Converts the Color to a ColorHsv
        [[nodiscard]]
        constexpr explicit operator ColorHsva() const;

        /// @brief Converts the Color to a Vector3
        [[nodiscard]]
        constexpr explicit operator Vector3() const;

        /// @brief Converts the Color to a Vector4
        [[nodiscard]]
        constexpr explicit operator Vector4() const;
    };

    /// @brief The ColorHsva struct represents a color in HSVA color space.
    ///
    /// It uses values from 0 to 1. The default alpha value is 1.
    struct MOUNTAIN_API ColorHsva
    {
        /// @brief Constant for white
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva White();

        /// @brief Constant for gray
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva Gray();

        /// @brief Constant for black
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva Black();

        /// @brief Constant for red
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva Red();

        /// @brief Constant for green
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva Green();

        /// @brief Constant for blue
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva Blue();

        /// @brief Constant for yellow
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva Yellow();

        /// @brief Constant for cyan
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva LightBlue();

        /// @brief Constant for magenta
        /// @return Color
        [[nodiscard]]
        static constexpr ColorHsva Magenta();

        /// @brief Hue component
        float_t h = 0;
        /// @brief Saturation component
        float_t s = 0;
        /// @brief Value component
        float_t v = 0;
        /// @brief Alpha component
        float_t a = 1.f;

        ColorHsva() = default;

        /// @brief Constructs a color with each specified component
        ///
        /// @param h Hue component
        /// @param s Saturation component
        /// @param v Value component
        /// @param a Alpha component
        [[nodiscard]]
        constexpr ColorHsva(const float_t h, const float_t s, const float_t v, const float_t a = 1.f)
        : h(h), s(s), v(v), a(a) {}

        /// @brief Converts the ColorHsva to a Color
        [[nodiscard]]
        constexpr explicit operator Color() const;

        /// @brief Converts the ColorHsva to a Vector3
        [[nodiscard]]
        constexpr explicit operator Vector3() const;

        /// @brief Converts the ColorHsva to a Vector4
        [[nodiscard]]
        constexpr explicit operator Vector4() const;
    };

    /// @brief Adds 2 Color, caps at @c 1.f
    /// @param c1 A
    /// @param c2 B
    /// @return A + B
    [[nodiscard]]
    constexpr Color operator+(const Color& c1, const Color& c2);

    /// @brief Multiplies 2 Color
    /// @param c1 A
    /// @param c2 B
    /// @return A * B
    [[nodiscard]]
    constexpr Color operator*(const Color& c1, const Color& c2);

    /// @brief Multiplies the alpha component of a Color
    /// @param color Color
    /// @param alphaFactor Alpha factor
    /// @return Color.a * alphaFactor
    [[nodiscard]]
    constexpr Color operator*(Color color, float_t alphaFactor);

    /// @brief Compares 2 Color component-wise
    /// @param c1 A
    /// @param c2 B
    /// @return A == B
    [[nodiscard]]
    constexpr bool_t operator==(const Color& c1, const Color& c2);

    /// @brief Compares 2 Color component-wise
    /// @param c1 A
    /// @param c2 B
    /// @return A != B
    [[nodiscard]]
    constexpr bool_t operator!=(const Color& c1, const Color& c2);

    /// @brief Multiplies the alpha component of a ColorHsva
    /// @param color Color
    /// @param alphaFactor Alpha factor
    /// @return Color.a * alphaFactor
    [[nodiscard]]
    constexpr ColorHsva operator*(const ColorHsva& color, float_t alphaFactor);

    /// @brief Compares 2 ColorHsva component-wise
    /// @param c1 A
    /// @param c2 B
    /// @return A == B
    [[nodiscard]]
    constexpr bool_t operator==(const ColorHsva& c1, const ColorHsva& c2);

    /// @brief Compares 2 ColorHsva component-wise
    /// @param c1 A
    /// @param c2 B
    /// @return A != B
    [[nodiscard]]
    constexpr bool_t operator!=(const ColorHsva& c1, const ColorHsva& c2);
}

/// @private
template <>
struct std::formatter<Mountain::Color>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;
 
        if (*it != '}')
            throw std::format_error("Invalid format args for Color");
 
        return it;
    }

    template <class FmtContext>
    typename FmtContext::iterator format(Mountain::Color c, FmtContext& ctx) const
    {
        std::ostringstream out;

        out << std::vformat("{:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + '}', std::make_format_args(c.r, c.g, c.b, c.a));

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }

private:
    std::string m_Format;
};

/// @private
template <>
struct std::formatter<Mountain::ColorHsva>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;
 
        if (*it != '}')
            throw std::format_error("Invalid format args for ColorHsva");
 
        return it;
    }

    template <class FmtContext>
    typename FmtContext::iterator format(Mountain::ColorHsva c, FmtContext& ctx) const
    {
        std::ostringstream out;

        out << std::vformat("{:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + '}', std::make_format_args(c.h, c.s, c.v, c.a));

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }

private:
    std::string m_Format;
};

namespace Calc
{
    [[nodiscard]]
    Mountain::Color Lerp(const Mountain::Color& value, const Mountain::Color& target, float_t time);

    [[nodiscard]]
    Mountain::Color Lerp(const Mountain::Color& value, const Mountain::Color& target, float_t time, Easing::Easer easer);
}

#include "Mountain/utils/color.inl"
