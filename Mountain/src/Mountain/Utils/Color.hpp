#pragma once

#include <format>
#include <sstream>

#include <Math/easing.hpp>
#include <Math/vector3.hpp>
#include <Math/vector4.hpp>

#include <ImGui/imgui.h>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/Requirements.hpp"

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

#pragma region Constants
        /// @brief Constant for Transparent.
        /// @return A color with all its components set to @c 0.f.
        static constexpr Color Transparent();

        /// @brief Constant for Alice Blue.
        /// @return Red = @c 0xF0, Green = @c 0xF8, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color AliceBlue();

        /// @brief Constant for Antique White.
        /// @return Red = @c 0xFA, Green = @c 0xEB, Blue = @c 0xD7, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color AntiqueWhite();

        /// @brief Constant for Aqua.
        /// @return Red = @c 0x00, Green = @c 0xFF, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Aqua();

        /// @brief Constant for Aquamarine.
        /// @return Red = @c 0x7F, Green = @c 0xFF, Blue = @c 0xD4, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Aquamarine();

        /// @brief Constant for Azure.
        /// @return Red = @c 0xF0, Green = @c 0xFF, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Azure();

        /// @brief Constant for Beige.
        /// @return Red = @c 0xF5, Green = @c 0xF5, Blue = @c 0xDC, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Beige();

        /// @brief Constant for Bisque.
        /// @return Red = @c 0xFF, Green = @c 0xE4, Blue = @c 0xC4, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Bisque();

        /// @brief Constant for Black.
        /// @return Red = @c 0x00, Green = @c 0x00, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Black();

        /// @brief Constant for Blanched Almond.
        /// @return Red = @c 0xFF, Green = @c 0xEB, Blue = @c 0xCD, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color BlanchedAlmond();

        /// @brief Constant for Blue.
        /// @return Red = @c 0x00, Green = @c 0x00, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Blue();

        /// @brief Constant for Blue Violet.
        /// @return Red = @c 0x8A, Green = @c 0x2B, Blue = @c 0xE2, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color BlueViolet();

        /// @brief Constant for Brown.
        /// @return Red = @c 0xA5, Green = @c 0x2A, Blue = @c 0x2A, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Brown();

        /// @brief Constant for Burly Wood.
        /// @return Red = @c 0xDE, Green = @c 0xB8, Blue = @c 0x87, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color BurlyWood();

        /// @brief Constant for Cadet Blue.
        /// @return Red = @c 0x5F, Green = @c 0x9E, Blue = @c 0xA0, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color CadetBlue();

        /// @brief Constant for Chartreuse.
        /// @return Red = @c 0x7F, Green = @c 0xFF, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Chartreuse();

        /// @brief Constant for Chocolate.
        /// @return Red = @c 0xD2, Green = @c 0x69, Blue = @c 0x1E, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Chocolate();

        /// @brief Constant for Coral.
        /// @return Red = @c 0xFF, Green = @c 0x7F, Blue = @c 0x50, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Coral();

        /// @brief Constant for Cornflower Blue.
        /// @return Red = @c 0x64, Green = @c 0x95, Blue = @c 0xED, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color CornflowerBlue();

        /// @brief Constant for Cornsilk.
        /// @return Red = @c 0xFF, Green = @c 0xF8, Blue = @c 0xDC, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Cornsilk();

        /// @brief Constant for Crimson.
        /// @return Red = @c 0xDC, Green = @c 0x14, Blue = @c 0x3C, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Crimson();

        /// @brief Constant for Cyan.
        /// @return Red = @c 0x00, Green = @c 0xFF, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Cyan();

        /// @brief Constant for Dark Blue.
        /// @return Red = @c 0x00, Green = @c 0x00, Blue = @c 0x8B, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkBlue();

        /// @brief Constant for Dark Cyan.
        /// @return Red = @c 0x00, Green = @c 0x8B, Blue = @c 0x8B, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkCyan();

        /// @brief Constant for Dark Goldenrod.
        /// @return Red = @c 0xB8, Green = @c 0x86, Blue = @c 0x0B, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkGoldenrod();

        /// @brief Constant for Dark Gray.
        /// @return Red = @c 0xA9, Green = @c 0xA9, Blue = @c 0xA9, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkGray();

        /// @brief Constant for Dark Green.
        /// @return Red = @c 0x00, Green = @c 0x64, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkGreen();

        /// @brief Constant for Dark Khaki.
        /// @return Red = @c 0xBD, Green = @c 0xB7, Blue = @c 0x6B, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkKhaki();

        /// @brief Constant for Dark Magenta.
        /// @return Red = @c 0x8B, Green = @c 0x00, Blue = @c 0x8B, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkMagenta();

        /// @brief Constant for Dark Olive Green.
        /// @return Red = @c 0x55, Green = @c 0x6B, Blue = @c 0x2F, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkOliveGreen();

        /// @brief Constant for Dark Orange.
        /// @return Red = @c 0xFF, Green = @c 0x8C, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkOrange();

        /// @brief Constant for Dark Orchid.
        /// @return Red = @c 0x99, Green = @c 0x32, Blue = @c 0xCC, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkOrchid();

        /// @brief Constant for Dark Red.
        /// @return Red = @c 0x8B, Green = @c 0x00, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkRed();

        /// @brief Constant for Dark Salmon.
        /// @return Red = @c 0xE9, Green = @c 0x96, Blue = @c 0x7A, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkSalmon();

        /// @brief Constant for Dark Sea Green.
        /// @return Red = @c 0x8F, Green = @c 0xBC, Blue = @c 0x8B, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkSeaGreen();

        /// @brief Constant for Dark Slate Blue.
        /// @return Red = @c 0x48, Green = @c 0x3D, Blue = @c 0x8B, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkSlateBlue();

        /// @brief Constant for Dark Slate Gray.
        /// @return Red = @c 0x2F, Green = @c 0x4F, Blue = @c 0x4F, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkSlateGray();

        /// @brief Constant for Dark Turquoise.
        /// @return Red = @c 0x00, Green = @c 0xCE, Blue = @c 0xD1, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkTurquoise();

        /// @brief Constant for Dark Violet.
        /// @return Red = @c 0x94, Green = @c 0x00, Blue = @c 0xD3, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DarkViolet();

        /// @brief Constant for Deep Pink.
        /// @return Red = @c 0xFF, Green = @c 0x14, Blue = @c 0x93, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DeepPink();

        /// @brief Constant for Deep Sky Blue.
        /// @return Red = @c 0x00, Green = @c 0xBF, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DeepSkyBlue();

        /// @brief Constant for Dim Gray.
        /// @return Red = @c 0x69, Green = @c 0x69, Blue = @c 0x69, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DimGray();

        /// @brief Constant for Dodger Blue.
        /// @return Red = @c 0x1E, Green = @c 0x90, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color DodgerBlue();

        /// @brief Constant for Firebrick.
        /// @return Red = @c 0xB2, Green = @c 0x22, Blue = @c 0x22, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Firebrick();

        /// @brief Constant for Floral White.
        /// @return Red = @c 0xFF, Green = @c 0xFA, Blue = @c 0xF0, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color FloralWhite();

        /// @brief Constant for Forest Green.
        /// @return Red = @c 0x22, Green = @c 0x8B, Blue = @c 0x22, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color ForestGreen();

        /// @brief Constant for Fuchsia.
        /// @return Red = @c 0xFF, Green = @c 0x00, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Fuchsia();

        /// @brief Constant for Gainsboro.
        /// @return Red = @c 0xDC, Green = @c 0xDC, Blue = @c 0xDC, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Gainsboro();

        /// @brief Constant for Ghost White.
        /// @return Red = @c 0xF8, Green = @c 0xF8, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color GhostWhite();

        /// @brief Constant for Gold.
        /// @return Red = @c 0xFF, Green = @c 0xD7, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Gold();

        /// @brief Constant for Goldenrod.
        /// @return Red = @c 0xDA, Green = @c 0xA5, Blue = @c 0x20, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Goldenrod();

        /// @brief Constant for Gray.
        /// @return Red = @c 0x80, Green = @c 0x80, Blue = @c 0x80, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Gray();

        /// @brief Constant for Green.
        /// @return Red = @c 0x00, Green = @c 0x80, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Green();

        /// @brief Constant for Green Yellow.
        /// @return Red = @c 0xAD, Green = @c 0xFF, Blue = @c 0x2F, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color GreenYellow();

        /// @brief Constant for Honeydew.
        /// @return Red = @c 0xF0, Green = @c 0xFF, Blue = @c 0xF0, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Honeydew();

        /// @brief Constant for Hot Pink.
        /// @return Red = @c 0xFF, Green = @c 0x69, Blue = @c 0xB4, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color HotPink();

        /// @brief Constant for Indian Red.
        /// @return Red = @c 0xCD, Green = @c 0x5C, Blue = @c 0x5C, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color IndianRed();

        /// @brief Constant for Indigo.
        /// @return Red = @c 0x4B, Green = @c 0x00, Blue = @c 0x82, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Indigo();

        /// @brief Constant for Ivory.
        /// @return Red = @c 0xFF, Green = @c 0xFF, Blue = @c 0xF0, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Ivory();

        /// @brief Constant for Khaki.
        /// @return Red = @c 0xF0, Green = @c 0xE6, Blue = @c 0x8C, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Khaki();

        /// @brief Constant for Lavender.
        /// @return Red = @c 0xE6, Green = @c 0xE6, Blue = @c 0xFA, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Lavender();

        /// @brief Constant for Lavender Blush.
        /// @return Red = @c 0xFF, Green = @c 0xF0, Blue = @c 0xF5, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LavenderBlush();

        /// @brief Constant for Lawn Green.
        /// @return Red = @c 0x7C, Green = @c 0xFC, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LawnGreen();

        /// @brief Constant for Lemon Chiffon.
        /// @return Red = @c 0xFF, Green = @c 0xFA, Blue = @c 0xCD, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LemonChiffon();

        /// @brief Constant for Light Blue.
        /// @return Red = @c 0xAD, Green = @c 0xD8, Blue = @c 0xE6, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightBlue();

        /// @brief Constant for Light Coral.
        /// @return Red = @c 0xF0, Green = @c 0x80, Blue = @c 0x80, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightCoral();

        /// @brief Constant for Light Cyan.
        /// @return Red = @c 0xE0, Green = @c 0xFF, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightCyan();

        /// @brief Constant for Light Goldenrod Yellow.
        /// @return Red = @c 0xFA, Green = @c 0xFA, Blue = @c 0xD2, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightGoldenrodYellow();

        /// @brief Constant for Light Gray.
        /// @return Red = @c 0xD3, Green = @c 0xD3, Blue = @c 0xD3, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightGray();

        /// @brief Constant for Light Green.
        /// @return Red = @c 0x90, Green = @c 0xEE, Blue = @c 0x90, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightGreen();

        /// @brief Constant for Light Pink.
        /// @return Red = @c 0xFF, Green = @c 0xB6, Blue = @c 0xC1, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightPink();

        /// @brief Constant for Light Salmon.
        /// @return Red = @c 0xFF, Green = @c 0xA0, Blue = @c 0x7A, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightSalmon();

        /// @brief Constant for Light Sea Green.
        /// @return Red = @c 0x20, Green = @c 0xB2, Blue = @c 0xAA, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightSeaGreen();

        /// @brief Constant for Light Sky Blue.
        /// @return Red = @c 0x87, Green = @c 0xCE, Blue = @c 0xFA, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightSkyBlue();

        /// @brief Constant for Light Slate Gray.
        /// @return Red = @c 0x77, Green = @c 0x88, Blue = @c 0x99, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightSlateGray();

        /// @brief Constant for Light Steel Blue.
        /// @return Red = @c 0xB0, Green = @c 0xC4, Blue = @c 0xDE, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightSteelBlue();

        /// @brief Constant for Light Yellow.
        /// @return Red = @c 0xFF, Green = @c 0xFF, Blue = @c 0xE0, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LightYellow();

        /// @brief Constant for Lime.
        /// @return Red = @c 0x00, Green = @c 0xFF, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Lime();

        /// @brief Constant for Lime Green.
        /// @return Red = @c 0x32, Green = @c 0xCD, Blue = @c 0x32, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color LimeGreen();

        /// @brief Constant for Linen.
        /// @return Red = @c 0xFA, Green = @c 0xF0, Blue = @c 0xE6, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Linen();

        /// @brief Constant for Magenta.
        /// @return Red = @c 0xFF, Green = @c 0x00, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Magenta();

        /// @brief Constant for Maroon.
        /// @return Red = @c 0x80, Green = @c 0x00, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Maroon();

        /// @brief Constant for Medium Aquamarine.
        /// @return Red = @c 0x66, Green = @c 0xCD, Blue = @c 0xAA, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumAquamarine();

        /// @brief Constant for Medium Blue.
        /// @return Red = @c 0x00, Green = @c 0x00, Blue = @c 0xCD, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumBlue();

        /// @brief Constant for Medium Orchid.
        /// @return Red = @c 0xBA, Green = @c 0x55, Blue = @c 0xD3, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumOrchid();

        /// @brief Constant for Medium Purple.
        /// @return Red = @c 0x93, Green = @c 0x70, Blue = @c 0xDB, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumPurple();

        /// @brief Constant for Medium Sea Green.
        /// @return Red = @c 0x3C, Green = @c 0xB3, Blue = @c 0x71, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumSeaGreen();

        /// @brief Constant for Medium Slate Blue.
        /// @return Red = @c 0x7B, Green = @c 0x68, Blue = @c 0xEE, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumSlateBlue();

        /// @brief Constant for Medium Spring Green.
        /// @return Red = @c 0x00, Green = @c 0xFA, Blue = @c 0x9A, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumSpringGreen();

        /// @brief Constant for Medium Turquoise.
        /// @return Red = @c 0x48, Green = @c 0xD1, Blue = @c 0xCC, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumTurquoise();

        /// @brief Constant for Medium Violet Red.
        /// @return Red = @c 0xC7, Green = @c 0x15, Blue = @c 0x85, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MediumVioletRed();

        /// @brief Constant for Midnight Blue.
        /// @return Red = @c 0x19, Green = @c 0x19, Blue = @c 0x70, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MidnightBlue();

        /// @brief Constant for Mint Cream.
        /// @return Red = @c 0xF5, Green = @c 0xFF, Blue = @c 0xFA, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MintCream();

        /// @brief Constant for Misty Rose.
        /// @return Red = @c 0xFF, Green = @c 0xE4, Blue = @c 0xE1, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MistyRose();

        /// @brief Constant for Moccasin.
        /// @return Red = @c 0xFF, Green = @c 0xE4, Blue = @c 0xB5, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Moccasin();

        /// @brief Constant for MonoGame Orange.
        /// @return Red = @c 0xE7, Green = @c 0x3C, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color MonoGameOrange();

        /// @brief Constant for Navajo White.
        /// @return Red = @c 0xFF, Green = @c 0xDE, Blue = @c 0xAD, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color NavajoWhite();

        /// @brief Constant for Navy.
        /// @return Red = @c 0x00, Green = @c 0x00, Blue = @c 0x80, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Navy();

        /// @brief Constant for Old Lace.
        /// @return Red = @c 0xFD, Green = @c 0xF5, Blue = @c 0xE6, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color OldLace();

        /// @brief Constant for Olive.
        /// @return Red = @c 0x80, Green = @c 0x80, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Olive();

        /// @brief Constant for Olive Drab.
        /// @return Red = @c 0x6B, Green = @c 0x8E, Blue = @c 0x23, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color OliveDrab();

        /// @brief Constant for Orange.
        /// @return Red = @c 0xFF, Green = @c 0xA5, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Orange();

        /// @brief Constant for Orange Red.
        /// @return Red = @c 0xFF, Green = @c 0x45, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color OrangeRed();

        /// @brief Constant for Orchid.
        /// @return Red = @c 0xDA, Green = @c 0x70, Blue = @c 0xD6, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Orchid();

        /// @brief Constant for Pale Goldenrod.
        /// @return Red = @c 0xEE, Green = @c 0xE8, Blue = @c 0xAA, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color PaleGoldenrod();

        /// @brief Constant for Pale Green.
        /// @return Red = @c 0x98, Green = @c 0xFB, Blue = @c 0x98, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color PaleGreen();

        /// @brief Constant for Pale Turquoise.
        /// @return Red = @c 0xAF, Green = @c 0xEE, Blue = @c 0xEE, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color PaleTurquoise();

        /// @brief Constant for Pale Violet Red.
        /// @return Red = @c 0xDB, Green = @c 0x70, Blue = @c 0x93, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color PaleVioletRed();

        /// @brief Constant for Papaya Whip.
        /// @return Red = @c 0xFF, Green = @c 0xEF, Blue = @c 0xD5, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color PapayaWhip();

        /// @brief Constant for Peach Puff.
        /// @return Red = @c 0xFF, Green = @c 0xDA, Blue = @c 0xB9, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color PeachPuff();

        /// @brief Constant for Peru.
        /// @return Red = @c 0xCD, Green = @c 0x85, Blue = @c 0x3F, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Peru();

        /// @brief Constant for Pink.
        /// @return Red = @c 0xFF, Green = @c 0xC0, Blue = @c 0xCB, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Pink();

        /// @brief Constant for Plum.
        /// @return Red = @c 0xDD, Green = @c 0xA0, Blue = @c 0xDD, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Plum();

        /// @brief Constant for Powder Blue.
        /// @return Red = @c 0xB0, Green = @c 0xE0, Blue = @c 0xE6, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color PowderBlue();

        /// @brief Constant for Purple.
        /// @return Red = @c 0x80, Green = @c 0x00, Blue = @c 0x80, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Purple();

        /// @brief Constant for Red.
        /// @return Red = @c 0xFF, Green = @c 0x00, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Red();

        /// @brief Constant for Rosy Brown.
        /// @return Red = @c 0xBC, Green = @c 0x8F, Blue = @c 0x8F, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color RosyBrown();

        /// @brief Constant for Royal Blue.
        /// @return Red = @c 0x41, Green = @c 0x69, Blue = @c 0xE1, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color RoyalBlue();

        /// @brief Constant for Saddle Brown.
        /// @return Red = @c 0x8B, Green = @c 0x45, Blue = @c 0x13, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SaddleBrown();

        /// @brief Constant for Salmon.
        /// @return Red = @c 0xFA, Green = @c 0x80, Blue = @c 0x72, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Salmon();

        /// @brief Constant for Sandy Brown.
        /// @return Red = @c 0xF4, Green = @c 0xA4, Blue = @c 0x60, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SandyBrown();

        /// @brief Constant for Sea Green.
        /// @return Red = @c 0x2E, Green = @c 0x8B, Blue = @c 0x57, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SeaGreen();

        /// @brief Constant for SeaShell.
        /// @return Red = @c 0xFF, Green = @c 0xF5, Blue = @c 0xEE, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SeaShell();

        /// @brief Constant for Sienna.
        /// @return Red = @c 0xA0, Green = @c 0x52, Blue = @c 0x2D, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Sienna();

        /// @brief Constant for Silver.
        /// @return Red = @c 0xC0, Green = @c 0xC0, Blue = @c 0xC0, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Silver();

        /// @brief Constant for Sky Blue.
        /// @return Red = @c 0x87, Green = @c 0xCE, Blue = @c 0xEB, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SkyBlue();

        /// @brief Constant for Slate Blue.
        /// @return Red = @c 0x6A, Green = @c 0x5A, Blue = @c 0xCD, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SlateBlue();

        /// @brief Constant for Slate Gray.
        /// @return Red = @c 0x70, Green = @c 0x80, Blue = @c 0x90, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SlateGray();

        /// @brief Constant for Snow.
        /// @return Red = @c 0xFF, Green = @c 0xFA, Blue = @c 0xFA, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Snow();

        /// @brief Constant for Spring Green.
        /// @return Red = @c 0x00, Green = @c 0xFF, Blue = @c 0x7F, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SpringGreen();

        /// @brief Constant for Steel Blue.
        /// @return Red = @c 0x46, Green = @c 0x82, Blue = @c 0xB4, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color SteelBlue();

        /// @brief Constant for Tan.
        /// @return Red = @c 0xD2, Green = @c 0xB4, Blue = @c 0x8C, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Tan();

        /// @brief Constant for Teal.
        /// @return Red = @c 0x00, Green = @c 0x80, Blue = @c 0x80, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Teal();

        /// @brief Constant for Thistle.
        /// @return Red = @c 0xD8, Green = @c 0xBF, Blue = @c 0xD8, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Thistle();

        /// @brief Constant for Tomato.
        /// @return Red = @c 0xFF, Green = @c 0x63, Blue = @c 0x47, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Tomato();

        /// @brief Constant for Turquoise.
        /// @return Red = @c 0x40, Green = @c 0xE0, Blue = @c 0xD0, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Turquoise();

        /// @brief Constant for Violet.
        /// @return Red = @c 0xEE, Green = @c 0x82, Blue = @c 0xEE, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Violet();

        /// @brief Constant for Wheat.
        /// @return Red = @c 0xF5, Green = @c 0xDE, Blue = @c 0xB3, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Wheat();

        /// @brief Constant for White.
        /// @return Red = @c 0xFF, Green = @c 0xFF, Blue = @c 0xFF, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color White();

        /// @brief Constant for White Smoke.
        /// @return Red = @c 0xF5, Green = @c 0xF5, Blue = @c 0xF5, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color WhiteSmoke();

        /// @brief Constant for Yellow.
        /// @return Red = @c 0xFF, Green = @c 0xFF, Blue = @c 0x00, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color Yellow();

        /// @brief Constant for Yellow Green.
        /// @return Red = @c 0x9A, Green = @c 0xCD, Blue = @c 0x32, Alpha = @c 0xFF, all divided by @c 0xFF to be between @c 0.f and @c 1.f.
        static constexpr Color YellowGreen();
#pragma endregion

        ATTRIBUTE_NODISCARD
        static constexpr Color FromHex(uint32_t rgba);

        /// @brief Red component
        float_t r = 0.f;
        /// @brief Green component
        float_t g = 0.f;
        /// @brief Blue component
        float_t b = 0.f;
        /// @brief Alpha component
        float_t a = 1.f;

        ATTRIBUTE_NODISCARD
        Color() = default;

        /// @brief Constructs a grayscale color with each component equal to @p rgb
        /// @param rgb Red, Green and Blue components
        /// @param a Alpha component
        ATTRIBUTE_NODISCARD
        explicit constexpr Color(float_t rgb, float_t a = 1.f);

        /// @brief Constructs a color with each specified component
        /// @param r Red component
        /// @param g Green component
        /// @param b Blue component
        /// @param a Alpha component
        ATTRIBUTE_NODISCARD
        constexpr Color(float_t r, float_t g, float_t b, float_t a = 1.f);

        /// @brief Constructs a color from a Vector3 and an alpha value
        /// @param rgb Red, Green and Blue components
        /// @param a Alpha component
        ATTRIBUTE_NODISCARD
        explicit constexpr Color(const Vector3& rgb, float_t a = 1.f);

        /// @brief Constructs a color from a Vector4
        /// @param rgba Color components
        ATTRIBUTE_NODISCARD
        explicit constexpr Color(const Vector4& rgba);

        /// @brief Constructs a color from four floats at the given pointer address
        /// @param data Color components
        ATTRIBUTE_NODISCARD
        explicit constexpr Color(const float_t* data);

        /// @brief Constructs a color from a 32-bit packed color value
        /// @param packedValue Packed color value, e.g., @c 0xFFFF0000 for @c Color::Blue()
        ATTRIBUTE_NODISCARD
        explicit constexpr Color(uint32_t packedValue);

        /// @brief Get a 32-bit packed value for this color in the following order: @c 0xAABBGGRR
        ATTRIBUTE_NODISCARD
        constexpr uint32_t GetPackedValue() const;

        ATTRIBUTE_NODISCARD
        constexpr float_t* Data();

        ATTRIBUTE_NODISCARD
        constexpr const float_t* Data() const;

        /// @brief Converts the @c Color to a @c ColorHsva
        ATTRIBUTE_NODISCARD
        constexpr explicit operator ColorHsva() const;

        /// @brief Converts the @c Color to a @c Vector3
        ATTRIBUTE_NODISCARD
        constexpr explicit operator Vector3() const;

        /// @brief Converts the @c Color to a @c Vector4
        ATTRIBUTE_NODISCARD
        constexpr explicit operator Vector4() const;

        /// @brief Converts the @c Color to a @c ImVec4
        ATTRIBUTE_NODISCARD
        // ReSharper disable once CppNonExplicitConversionOperator
        operator ImVec4() const;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, Color);

    /// @brief The ColorHsva struct represents a color in HSVA color space.
    ///
    /// It uses values from 0 to 1. The default alpha value is 1.
    struct MOUNTAIN_API ColorHsva
    {
        /// @brief Constant for white
        ATTRIBUTE_NODISCARD
        static constexpr ColorHsva White();

        /// @brief Constant for gray
        ATTRIBUTE_NODISCARD
        static constexpr ColorHsva Gray();

        /// @brief Constant for black
        ATTRIBUTE_NODISCARD
        static constexpr ColorHsva Black();

        /// @brief Constant for red
        ATTRIBUTE_NODISCARD
        static constexpr ColorHsva Red();

        /// @brief Constant for green
        ATTRIBUTE_NODISCARD
        static constexpr ColorHsva Green();

        /// @brief Constant for blue
        ATTRIBUTE_NODISCARD
        static constexpr ColorHsva Blue();

        /// @brief Constant for yellow
        ATTRIBUTE_NODISCARD
        static constexpr ColorHsva Yellow();

        /// @brief Constant for cyan
        ATTRIBUTE_NODISCARD
        static constexpr ColorHsva LightBlue();

        /// @brief Constant for magenta
        ATTRIBUTE_NODISCARD
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
        /// @param h Hue component
        /// @param s Saturation component
        /// @param v Value component
        /// @param a Alpha component
        ATTRIBUTE_NODISCARD
        constexpr ColorHsva(float_t h, float_t s, float_t v, float_t a = 1.f);

        /// @brief Converts the @c ColorHsva to a @c Color
        ATTRIBUTE_NODISCARD
        constexpr explicit operator Color() const;

        /// @brief Converts the @c ColorHsva to a @c Vector3
        ATTRIBUTE_NODISCARD
        constexpr explicit operator Vector3() const;

        /// @brief Converts the @c ColorHsva to a @c Vector4
        ATTRIBUTE_NODISCARD
        constexpr explicit operator Vector4() const;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, ColorHsva);

    /// @brief Adds two Color, caps at @c 1.f
    /// @param c1 A
    /// @param c2 B
    /// @return A + B
    ATTRIBUTE_NODISCARD
    constexpr Color operator+(const Color& c1, const Color& c2);

    /// @brief Multiplies two Color
    /// @param c1 A
    /// @param c2 B
    /// @return A * B
    ATTRIBUTE_NODISCARD
    constexpr Color operator*(const Color& c1, const Color& c2);

    /// @brief Multiplies the alpha component of a Color
    /// @param color Color
    /// @param alphaFactor Alpha factor
    /// @return Color.a * alphaFactor
    ATTRIBUTE_NODISCARD
    constexpr Color operator*(Color color, float_t alphaFactor);

    /// @brief Compares two Color component-wise
    /// @param c1 A
    /// @param c2 B
    /// @return A == B
    ATTRIBUTE_NODISCARD
    constexpr bool_t operator==(const Color& c1, const Color& c2);

    /// @brief Compares two Color component-wise
    /// @param c1 A
    /// @param c2 B
    /// @return A != B
    ATTRIBUTE_NODISCARD
    constexpr bool_t operator!=(const Color& c1, const Color& c2);

    /// @brief Multiplies the alpha component of a ColorHsva
    /// @param color Color
    /// @param alphaFactor Alpha factor
    /// @return Color.a * alphaFactor
    ATTRIBUTE_NODISCARD
    constexpr ColorHsva operator*(const ColorHsva& color, float_t alphaFactor);

    /// @brief Compares two ColorHsva component-wise
    /// @param c1 A
    /// @param c2 B
    /// @return A == B
    ATTRIBUTE_NODISCARD
    constexpr bool_t operator==(const ColorHsva& c1, const ColorHsva& c2);

    /// @brief Compares two ColorHsva component-wise
    /// @param c1 A
    /// @param c2 B
    /// @return A != B
    ATTRIBUTE_NODISCARD
    constexpr bool_t operator!=(const ColorHsva& c1, const ColorHsva& c2);
}

namespace Calc
{
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Mountain::Color Lerp(const Mountain::Color& value, const Mountain::Color& target, float_t time);

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Mountain::Color Lerp(const Mountain::Color& value, const Mountain::Color& target, float_t time, Easing::Easer easer);

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Mountain::Color LerpFixed(const Mountain::Color& value, const Mountain::Color& target, float_t time);

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Mountain::Color LerpFixed(const Mountain::Color& value, const Mountain::Color& target, float_t time, Easing::Easer easer);
}

// Start of Color.inl

#include <algorithm>

#include "Math/calc.hpp"

namespace Mountain
{
    static constexpr float_t HueCircle = 1.f; // A circle is 360 degrees, normalized as 1 here
    static constexpr float_t HueCircleOver3 = HueCircle / 3.f;
    static constexpr float_t HueCircleOver6 = HueCircle / 6.f;

#pragma region ConstantsImplemetation
    constexpr Color Color::Transparent() { return Color{0.f, 0.f, 0.f, 0.f}; }
    constexpr Color Color::AliceBlue() { return Color{0xF0 / 255.f, 0xF8 / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::AntiqueWhite() { return Color{0xFA / 255.f, 0xEB / 255.f, 0xD7 / 255.f}; }
    constexpr Color Color::Aqua() { return Color{0x00 / 255.f, 0xFF / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::Aquamarine() { return Color{0x7F / 255.f, 0xFF / 255.f, 0xD4 / 255.f}; }
    constexpr Color Color::Azure() { return Color{0xF0 / 255.f, 0xFF / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::Beige() { return Color{0xF5 / 255.f, 0xF5 / 255.f, 0xDC / 255.f}; }
    constexpr Color Color::Bisque() { return Color{0xFF / 255.f, 0xE4 / 255.f, 0xC4 / 255.f}; }
    constexpr Color Color::Black() { return Color{0.f, 0.f, 0.f}; }
    constexpr Color Color::BlanchedAlmond() { return Color{0xFF / 255.f, 0xEB / 255.f, 0xCD / 255.f}; }
    constexpr Color Color::Blue() { return Color{0x00 / 255.f, 0x00 / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::BlueViolet() { return Color{0x8A / 255.f, 0x2B / 255.f, 0xE2 / 255.f}; }
    constexpr Color Color::Brown() { return Color{0xA5 / 255.f, 0x2A / 255.f, 0x2A / 255.f}; }
    constexpr Color Color::BurlyWood() { return Color{0xDE / 255.f, 0xB8 / 255.f, 0x87 / 255.f}; }
    constexpr Color Color::CadetBlue() { return Color{0x5F / 255.f, 0x9E / 255.f, 0xA0 / 255.f}; }
    constexpr Color Color::Chartreuse() { return Color{0x7F / 255.f, 0xFF / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::Chocolate() { return Color{0xD2 / 255.f, 0x69 / 255.f, 0x1E / 255.f}; }
    constexpr Color Color::Coral() { return Color{0xFF / 255.f, 0x7F / 255.f, 0x50 / 255.f}; }
    constexpr Color Color::CornflowerBlue() { return Color{0x64 / 255.f, 0x95 / 255.f, 0xED / 255.f}; }
    constexpr Color Color::Cornsilk() { return Color{0xFF / 255.f, 0xF8 / 255.f, 0xDC / 255.f}; }
    constexpr Color Color::Crimson() { return Color{0xDC / 255.f, 0x14 / 255.f, 0x3C / 255.f}; }
    constexpr Color Color::Cyan() { return Color{0x00 / 255.f, 0xFF / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::DarkBlue() { return Color{0x00 / 255.f, 0x00 / 255.f, 0x8B / 255.f}; }
    constexpr Color Color::DarkCyan() { return Color{0x00 / 255.f, 0x8B / 255.f, 0x8B / 255.f}; }
    constexpr Color Color::DarkGoldenrod() { return Color{0xB8 / 255.f, 0x86 / 255.f, 0x0B / 255.f}; }
    constexpr Color Color::DarkGray() { return Color{0xA9 / 255.f, 0xA9 / 255.f, 0xA9 / 255.f}; }
    constexpr Color Color::DarkGreen() { return Color{0x00 / 255.f, 0x64 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::DarkKhaki() { return Color{0xBD / 255.f, 0xB7 / 255.f, 0x6B / 255.f}; }
    constexpr Color Color::DarkMagenta() { return Color{0x8B / 255.f, 0x00 / 255.f, 0x8B / 255.f}; }
    constexpr Color Color::DarkOliveGreen() { return Color{0x55 / 255.f, 0x6B / 255.f, 0x2F / 255.f}; }
    constexpr Color Color::DarkOrange() { return Color{0xFF / 255.f, 0x8C / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::DarkOrchid() { return Color{0x99 / 255.f, 0x32 / 255.f, 0xCC / 255.f}; }
    constexpr Color Color::DarkRed() { return Color{0x8B / 255.f, 0x00 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::DarkSalmon() { return Color{0xE9 / 255.f, 0x96 / 255.f, 0x7A / 255.f}; }
    constexpr Color Color::DarkSeaGreen() { return Color{0x8F / 255.f, 0xBC / 255.f, 0x8B / 255.f}; }
    constexpr Color Color::DarkSlateBlue() { return Color{0x48 / 255.f, 0x3D / 255.f, 0x8B / 255.f}; }
    constexpr Color Color::DarkSlateGray() { return Color{0x2F / 255.f, 0x4F / 255.f, 0x4F / 255.f}; }
    constexpr Color Color::DarkTurquoise() { return Color{0x00 / 255.f, 0xCE / 255.f, 0xD1 / 255.f}; }
    constexpr Color Color::DarkViolet() { return Color{0x94 / 255.f, 0x00 / 255.f, 0xD3 / 255.f}; }
    constexpr Color Color::DeepPink() { return Color{0xFF / 255.f, 0x14 / 255.f, 0x93 / 255.f}; }
    constexpr Color Color::DeepSkyBlue() { return Color{0x00 / 255.f, 0xBF / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::DimGray() { return Color{0x69 / 255.f, 0x69 / 255.f, 0x69 / 255.f}; }
    constexpr Color Color::DodgerBlue() { return Color{0x1E / 255.f, 0x90 / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::Firebrick() { return Color{0xB2 / 255.f, 0x22 / 255.f, 0x22 / 255.f}; }
    constexpr Color Color::FloralWhite() { return Color{0xFF / 255.f, 0xFA / 255.f, 0xF0 / 255.f}; }
    constexpr Color Color::ForestGreen() { return Color{0x22 / 255.f, 0x8B / 255.f, 0x22 / 255.f}; }
    constexpr Color Color::Fuchsia() { return Color{0xFF / 255.f, 0x00 / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::Gainsboro() { return Color{0xDC / 255.f, 0xDC / 255.f, 0xDC / 255.f}; }
    constexpr Color Color::GhostWhite() { return Color{0xF8 / 255.f, 0xF8 / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::Gold() { return Color{0xFF / 255.f, 0xD7 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::Goldenrod() { return Color{0xDA / 255.f, 0xA5 / 255.f, 0x20 / 255.f}; }
    constexpr Color Color::Gray() { return Color{0x80 / 255.f, 0x80 / 255.f, 0x80 / 255.f}; }
    constexpr Color Color::Green() { return Color{0x00 / 255.f, 0x80 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::GreenYellow() { return Color{0xAD / 255.f, 0xFF / 255.f, 0x2F / 255.f}; }
    constexpr Color Color::Honeydew() { return Color{0xF0 / 255.f, 0xFF / 255.f, 0xF0 / 255.f}; }
    constexpr Color Color::HotPink() { return Color{0xFF / 255.f, 0x69 / 255.f, 0xB4 / 255.f}; }
    constexpr Color Color::IndianRed() { return Color{0xCD / 255.f, 0x5C / 255.f, 0x5C / 255.f}; }
    constexpr Color Color::Indigo() { return Color{0x4B / 255.f, 0x00 / 255.f, 0x82 / 255.f}; }
    constexpr Color Color::Ivory() { return Color{0xFF / 255.f, 0xFF / 255.f, 0xF0 / 255.f}; }
    constexpr Color Color::Khaki() { return Color{0xF0 / 255.f, 0xE6 / 255.f, 0x8C / 255.f}; }
    constexpr Color Color::Lavender() { return Color{0xE6 / 255.f, 0xE6 / 255.f, 0xFA / 255.f}; }
    constexpr Color Color::LavenderBlush() { return Color{0xFF / 255.f, 0xF0 / 255.f, 0xF5 / 255.f}; }
    constexpr Color Color::LawnGreen() { return Color{0x7C / 255.f, 0xFC / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::LemonChiffon() { return Color{0xFF / 255.f, 0xFA / 255.f, 0xCD / 255.f}; }
    constexpr Color Color::LightBlue() { return Color{0xAD / 255.f, 0xD8 / 255.f, 0xE6 / 255.f}; }
    constexpr Color Color::LightCoral() { return Color{0xF0 / 255.f, 0x80 / 255.f, 0x80 / 255.f}; }
    constexpr Color Color::LightCyan() { return Color{0xE0 / 255.f, 0xFF / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::LightGoldenrodYellow() { return Color{0xFA / 255.f, 0xFA / 255.f, 0xD2 / 255.f}; }
    constexpr Color Color::LightGray() { return Color{0xD3 / 255.f, 0xD3 / 255.f, 0xD3 / 255.f}; }
    constexpr Color Color::LightGreen() { return Color{0x90 / 255.f, 0xEE / 255.f, 0x90 / 255.f}; }
    constexpr Color Color::LightPink() { return Color{0xFF / 255.f, 0xB6 / 255.f, 0xC1 / 255.f}; }
    constexpr Color Color::LightSalmon() { return Color{0xFF / 255.f, 0xA0 / 255.f, 0x7A / 255.f}; }
    constexpr Color Color::LightSeaGreen() { return Color{0x20 / 255.f, 0xB2 / 255.f, 0xAA / 255.f}; }
    constexpr Color Color::LightSkyBlue() { return Color{0x87 / 255.f, 0xCE / 255.f, 0xFA / 255.f}; }
    constexpr Color Color::LightSlateGray() { return Color{0x77 / 255.f, 0x88 / 255.f, 0x99 / 255.f}; }
    constexpr Color Color::LightSteelBlue() { return Color{0xB0 / 255.f, 0xC4 / 255.f, 0xDE / 255.f}; }
    constexpr Color Color::LightYellow() { return Color{0xFF / 255.f, 0xFF / 255.f, 0xE0 / 255.f}; }
    constexpr Color Color::Lime() { return Color{0x00 / 255.f, 0xFF / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::LimeGreen() { return Color{0x32 / 255.f, 0xCD / 255.f, 0x32 / 255.f}; }
    constexpr Color Color::Linen() { return Color{0xFA / 255.f, 0xF0 / 255.f, 0xE6 / 255.f}; }
    constexpr Color Color::Magenta() { return Color{0xFF / 255.f, 0x00 / 255.f, 0xFF / 255.f}; }
    constexpr Color Color::Maroon() { return Color{0x80 / 255.f, 0x00 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::MediumAquamarine() { return Color{0x66 / 255.f, 0xCD / 255.f, 0xAA / 255.f}; }
    constexpr Color Color::MediumBlue() { return Color{0x00 / 255.f, 0x00 / 255.f, 0xCD / 255.f}; }
    constexpr Color Color::MediumOrchid() { return Color{0xBA / 255.f, 0x55 / 255.f, 0xD3 / 255.f}; }
    constexpr Color Color::MediumPurple() { return Color{0x93 / 255.f, 0x70 / 255.f, 0xDB / 255.f}; }
    constexpr Color Color::MediumSeaGreen() { return Color{0x3C / 255.f, 0xB3 / 255.f, 0x71 / 255.f}; }
    constexpr Color Color::MediumSlateBlue() { return Color{0x7B / 255.f, 0x68 / 255.f, 0xEE / 255.f}; }
    constexpr Color Color::MediumSpringGreen() { return Color{0x00 / 255.f, 0xFA / 255.f, 0x9A / 255.f}; }
    constexpr Color Color::MediumTurquoise() { return Color{0x48 / 255.f, 0xD1 / 255.f, 0xCC / 255.f}; }
    constexpr Color Color::MediumVioletRed() { return Color{0xC7 / 255.f, 0x15 / 255.f, 0x85 / 255.f}; }
    constexpr Color Color::MidnightBlue() { return Color{0x19 / 255.f, 0x19 / 255.f, 0x70 / 255.f}; }
    constexpr Color Color::MintCream() { return Color{0xF5 / 255.f, 0xFF / 255.f, 0xFA / 255.f}; }
    constexpr Color Color::MistyRose() { return Color{0xFF / 255.f, 0xE4 / 255.f, 0xE1 / 255.f}; }
    constexpr Color Color::Moccasin() { return Color{0xFF / 255.f, 0xE4 / 255.f, 0xB5 / 255.f}; }
    constexpr Color Color::MonoGameOrange() { return Color{0xE7 / 255.f, 0x3C / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::NavajoWhite() { return Color{0xFF / 255.f, 0xDE / 255.f, 0xAD / 255.f}; }
    constexpr Color Color::Navy() { return Color{0x00 / 255.f, 0x00 / 255.f, 0x80 / 255.f}; }
    constexpr Color Color::OldLace() { return Color{0xFD / 255.f, 0xF5 / 255.f, 0xE6 / 255.f}; }
    constexpr Color Color::Olive() { return Color{0x80 / 255.f, 0x80 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::OliveDrab() { return Color{0x6B / 255.f, 0x8E / 255.f, 0x23 / 255.f}; }
    constexpr Color Color::Orange() { return Color{0xFF / 255.f, 0xA5 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::OrangeRed() { return Color{0xFF / 255.f, 0x45 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::Orchid() { return Color{0xDA / 255.f, 0x70 / 255.f, 0xD6 / 255.f}; }
    constexpr Color Color::PaleGoldenrod() { return Color{0xEE / 255.f, 0xE8 / 255.f, 0xAA / 255.f}; }
    constexpr Color Color::PaleGreen() { return Color{0x98 / 255.f, 0xFB / 255.f, 0x98 / 255.f}; }
    constexpr Color Color::PaleTurquoise() { return Color{0xAF / 255.f, 0xEE / 255.f, 0xEE / 255.f}; }
    constexpr Color Color::PaleVioletRed() { return Color{0xDB / 255.f, 0x70 / 255.f, 0x93 / 255.f}; }
    constexpr Color Color::PapayaWhip() { return Color{0xFF / 255.f, 0xEF / 255.f, 0xD5 / 255.f}; }
    constexpr Color Color::PeachPuff() { return Color{0xFF / 255.f, 0xDA / 255.f, 0xB9 / 255.f}; }
    constexpr Color Color::Peru() { return Color{0xCD / 255.f, 0x85 / 255.f, 0x3F / 255.f}; }
    constexpr Color Color::Pink() { return Color{0xFF / 255.f, 0xC0 / 255.f, 0xCB / 255.f}; }
    constexpr Color Color::Plum() { return Color{0xDD / 255.f, 0xA0 / 255.f, 0xDD / 255.f}; }
    constexpr Color Color::PowderBlue() { return Color{0xB0 / 255.f, 0xE0 / 255.f, 0xE6 / 255.f}; }
    constexpr Color Color::Purple() { return Color{0x80 / 255.f, 0x00 / 255.f, 0x80 / 255.f}; }
    constexpr Color Color::Red() { return Color{0xFF / 255.f, 0x00 / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::RosyBrown() { return Color{0xBC / 255.f, 0x8F / 255.f, 0x8F / 255.f}; }
    constexpr Color Color::RoyalBlue() { return Color{0x41 / 255.f, 0x69 / 255.f, 0xE1 / 255.f}; }
    constexpr Color Color::SaddleBrown() { return Color{0x8B / 255.f, 0x45 / 255.f, 0x13 / 255.f}; }
    constexpr Color Color::Salmon() { return Color{0xFA / 255.f, 0x80 / 255.f, 0x72 / 255.f}; }
    constexpr Color Color::SandyBrown() { return Color{0xF4 / 255.f, 0xA4 / 255.f, 0x60 / 255.f}; }
    constexpr Color Color::SeaGreen() { return Color{0x2E / 255.f, 0x8B / 255.f, 0x57 / 255.f}; }
    constexpr Color Color::SeaShell() { return Color{0xFF / 255.f, 0xF5 / 255.f, 0xEE / 255.f}; }
    constexpr Color Color::Sienna() { return Color{0xA0 / 255.f, 0x52 / 255.f, 0x2D / 255.f}; }
    constexpr Color Color::Silver() { return Color{0xC0 / 255.f, 0xC0 / 255.f, 0xC0 / 255.f}; }
    constexpr Color Color::SkyBlue() { return Color{0x87 / 255.f, 0xCE / 255.f, 0xEB / 255.f}; }
    constexpr Color Color::SlateBlue() { return Color{0x6A / 255.f, 0x5A / 255.f, 0xCD / 255.f}; }
    constexpr Color Color::SlateGray() { return Color{0x70 / 255.f, 0x80 / 255.f, 0x90 / 255.f}; }
    constexpr Color Color::Snow() { return Color{0xFF / 255.f, 0xFA / 255.f, 0xFA / 255.f}; }
    constexpr Color Color::SpringGreen() { return Color{0x00 / 255.f, 0xFF / 255.f, 0x7F / 255.f}; }
    constexpr Color Color::SteelBlue() { return Color{0x46 / 255.f, 0x82 / 255.f, 0xB4 / 255.f}; }
    constexpr Color Color::Tan() { return Color{0xD2 / 255.f, 0xB4 / 255.f, 0x8C / 255.f}; }
    constexpr Color Color::Teal() { return Color{0x00 / 255.f, 0x80 / 255.f, 0x80 / 255.f}; }
    constexpr Color Color::Thistle() { return Color{0xD8 / 255.f, 0xBF / 255.f, 0xD8 / 255.f}; }
    constexpr Color Color::Tomato() { return Color{0xFF / 255.f, 0x63 / 255.f, 0x47 / 255.f}; }
    constexpr Color Color::Turquoise() { return Color{0x40 / 255.f, 0xE0 / 255.f, 0xD0 / 255.f}; }
    constexpr Color Color::Violet() { return Color{0xEE / 255.f, 0x82 / 255.f, 0xEE / 255.f}; }
    constexpr Color Color::Wheat() { return Color{0xF5 / 255.f, 0xDE / 255.f, 0xB3 / 255.f}; }
    constexpr Color Color::White() { return Color{1.f, 1.f, 1.f}; }
    constexpr Color Color::WhiteSmoke() { return Color{0xF5 / 255.f, 0xF5 / 255.f, 0xF5 / 255.f}; }
    constexpr Color Color::Yellow() { return Color{0xFF / 255.f, 0xFF / 255.f, 0x00 / 255.f}; }
    constexpr Color Color::YellowGreen() { return Color{0x9A / 255.f, 0xCD / 255.f, 0x32 / 255.f}; }
#pragma endregion

    constexpr Color Color::FromHex(const uint32_t rgba)
    {
        return Color{static_cast<uint32_t>(_byteswap_ulong(rgba))};
    }

    constexpr Color::Color(const float_t rgb, const float_t a): r(rgb), g(rgb), b(rgb), a(a) {}

    constexpr Color::Color(const float_t r, const float_t g, const float_t b, const float_t a): r(r), g(g), b(b), a(a) {}

    constexpr Color::Color(const Vector3& rgb, const float_t a): r(rgb.x), g(rgb.y), b(rgb.z), a(a) {}

    constexpr Color::Color(const Vector4& rgba): r(rgba.x), g(rgba.y), b(rgba.z), a(rgba.w) {}

    constexpr Color::Color(const float_t* data): r(data[0]), g(data[1]), b(data[2]), a(data[3]) {}

    constexpr Color::Color(const uint32_t packedValue)
        : r(static_cast<float_t>(packedValue & 0xFF) / std::numeric_limits<uint8_t>::max())
        , g(static_cast<float_t>(packedValue >> 8 & 0xFF) / std::numeric_limits<uint8_t>::max())
        , b(static_cast<float_t>(packedValue >> 16 & 0xFF) / std::numeric_limits<uint8_t>::max())
        , a(static_cast<float_t>(packedValue >> 24) / std::numeric_limits<uint8_t>::max())
    {
    }

    constexpr uint32_t Color::GetPackedValue() const
    {
        const uint8_t byteR = static_cast<uint8_t>(Calc::Round(r * std::numeric_limits<uint8_t>::max()));
        const uint8_t byteG = static_cast<uint8_t>(Calc::Round(g * std::numeric_limits<uint8_t>::max()));
        const uint8_t byteB = static_cast<uint8_t>(Calc::Round(b * std::numeric_limits<uint8_t>::max()));
        const uint8_t byteA = static_cast<uint8_t>(Calc::Round(a * std::numeric_limits<uint8_t>::max()));

        return byteA << 24 | byteB << 16 | byteG << 8 | byteR;
    }

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
