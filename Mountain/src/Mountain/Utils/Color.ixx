export module Mountain:Utils_Color;

import <ImGui/imgui.h>;

import "Mountain/Core.hpp";

import std;
export import :Core;

/// @file Color.ixx
/// @brief Defines multiple color structs.

export namespace Mountain
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
        explicit constexpr Color(float_t rgb, float_t a = 1.f);

        /// @brief Constructs a color with each specified component
        ///
        /// @param r Red component
        /// @param g Green component
        /// @param b Blue component
        /// @param a Alpha component
        [[nodiscard]]
        constexpr Color(float_t r, float_t g, float_t b, float_t a = 1.f);

        /// @brief Constructs a color from a Vector3 and an alpha value
        ///
        /// @param rgb Red, Green and Blue components
        /// @param a Alpha component
        [[nodiscard]]
        explicit constexpr Color(const Vector3& rgb, float_t a = 1.f);

        /// @brief Constructs a color from a Vector4
        ///
        /// @param rgba Color components
        [[nodiscard]]
        explicit constexpr Color(const Vector4& rgba);

        /// @brief Constructs a color from four floats at the given pointer address
        ///
        /// @param data Color components
        [[nodiscard]]
        explicit constexpr Color(const float* data);

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

        /// @brief Converts the Color to a ImVec4
        [[nodiscard]]
        explicit operator ImVec4() const;
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
        constexpr ColorHsva(float_t h, float_t s, float_t v, float_t a = 1.f);

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
export template <>
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
export template <>
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

export namespace Calc
{
    [[nodiscard]]
    MOUNTAIN_API Mountain::Color Lerp(const Mountain::Color& value, const Mountain::Color& target, float_t time);

    [[nodiscard]]
    MOUNTAIN_API Mountain::Color Lerp(const Mountain::Color& value, const Mountain::Color& target, float_t time, Easing::Easer easer);

    [[nodiscard]]
    MOUNTAIN_API Mountain::Color LerpFixed(const Mountain::Color& value, const Mountain::Color& target, float_t time);

    [[nodiscard]]
    MOUNTAIN_API Mountain::Color LerpFixed(const Mountain::Color& value, const Mountain::Color& target, float_t time, Easing::Easer easer);
}

// Start of Color.inl

namespace Mountain
{
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

    constexpr Color::Color(const float_t rgb, const float_t a): r(rgb), g(rgb), b(rgb), a(a) {}

    constexpr Color::Color(const float_t r, const float_t g, const float_t b, const float_t a): r(r), g(g), b(b), a(a) {}

    constexpr Color::Color(const Vector3& rgb, const float_t a): r(rgb.x), g(rgb.y), b(rgb.z), a(a) {}

    constexpr Color::Color(const Vector4& rgba): r(rgba.x), g(rgba.y), b(rgba.z), a(rgba.w) {}

    constexpr Color::Color(const float* data): r(data[0]), g(data[1]), b(data[2]), a(data[3]) {}

    constexpr float_t* Color::Data() { return &r; }

    constexpr const float_t* Color::Data() const { return &r; }

    constexpr Color::operator ColorHsva() const
    {
        ColorHsva hsv = { 0.f, 0.f, 0.f, a };
        const float_t minVal = std::min({r, g, b});
        const float_t maxVal = std::max({r, g, b});
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

    constexpr Color::operator Vector3() const { return Vector3{r, g, b}; }

    constexpr Color::operator Vector4() const { return Vector4{r, g, b, a}; }

    constexpr ColorHsva ColorHsva::White() { return ColorHsva{0.f, 0.f, 1.f}; }

    constexpr ColorHsva ColorHsva::Gray() { return ColorHsva{0.f, 0.f, 0.5f}; }

    constexpr ColorHsva ColorHsva::Black() { return ColorHsva{0.f, 0.f, 0.f}; }

    constexpr ColorHsva ColorHsva::Red() { return ColorHsva{0.f, 1.f, 1.f}; }

    constexpr ColorHsva ColorHsva::Green() { return ColorHsva{HueCircleOver3, 1.f, 1.f}; }

    constexpr ColorHsva ColorHsva::Blue() { return ColorHsva{HueCircleOver3 * 2, 1.f, 1.f}; }

    constexpr ColorHsva ColorHsva::Yellow() { return ColorHsva{HueCircleOver6, 1.f, 1.f}; }

    constexpr ColorHsva ColorHsva::LightBlue() { return ColorHsva{HueCircleOver3 + HueCircleOver6, 1.f, 1.f}; }

    constexpr ColorHsva ColorHsva::Magenta() { return ColorHsva{HueCircleOver3 * 2 + HueCircleOver6, 1.f, 1.f}; }

    constexpr ColorHsva::ColorHsva(const float_t h, const float_t s, const float_t v, const float_t a): h(h), s(s), v(v), a(a) {}

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
}
