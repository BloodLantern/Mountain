#pragma once

#include "Mountain/core.hpp"

/// @file keyboard_input.hpp
/// @brief Defines enumerators related to keyboard input

namespace Mountain
{
    /// @brief %List of keyboard buttons
    enum class Key : uint16_t
    {
        /* Printable keys */
        /// @brief Space
        Space              = 32,
        /// @brief '
        Apostrophe         = 39,
        /// @brief ,
        Comma              = 44,
        /// @brief \-
        Minus              = 45,
        /// @brief \.
        Period             = 46,
        /// @brief /
        Slash              = 47,
        /// @brief Key0
        Key0               = 48,
        /// @brief Key1
        Key1               = 49,
        /// @brief Key2
        Key2               = 50,
        /// @brief Key3
        Key3               = 51,
        /// @brief Key4
        Key4               = 52,
        /// @brief Key5
        Key5               = 53,
        /// @brief Key6
        Key6               = 54,
        /// @brief Key7
        Key7               = 55,
        /// @brief Key8
        Key8               = 56,
        /// @brief Key9
        Key9               = 57,
        /// @brief ;
        Semicolon          = 59,
        /// @brief =
        Equal              = 61,
        /// @brief A
        A                  = 65,
        /// @brief B
        B                  = 66,
        /// @brief C
        C                  = 67,
        /// @brief D
        D                  = 68,
        /// @brief E
        E                  = 69,
        /// @brief F
        F                  = 70,
        /// @brief G
        G                  = 71,
        /// @brief H
        H                  = 72,
        /// @brief I
        I                  = 73,
        /// @brief J
        J                  = 74,
        /// @brief K
        K                  = 75,
        /// @brief L
        L                  = 76,
        /// @brief M
        M                  = 77,
        /// @brief N
        N                  = 78,
        /// @brief O
        O                  = 79,
        /// @brief P
        P                  = 80,
        /// @brief Q
        Q                  = 81,
        /// @brief R
        R                  = 82,
        /// @brief S
        S                  = 83,
        /// @brief T
        T                  = 84,
        /// @brief U
        U                  = 85,
        /// @brief V
        V                  = 86,
        /// @brief W
        W                  = 87,
        /// @brief X
        X                  = 88,
        /// @brief Y
        Y                  = 89,
        /// @brief Z
        Z                  = 90,

        /// @brief [
        LeftBracket        = 91,
        /// @brief Backslash
        Backslash          = 92,
        /// @brief ]
        RightBracket       = 93,
        /// @brief `
        GraveAccent        = 96,
        /// @brief World1 non-US #1
        World1             = 161,
        /// @brief World2 non-US #2
        World2             = 162,


        /* Function keys */
        /// @brief Escape
        Escape             = 256,
        /// @brief Enter
        Enter              = 257,
        /// @brief Tab
        Tab                = 258,
        /// @brief Backspace
        Backspace          = 259,
        /// @brief Insert
        Insert             = 260,
        /// @brief Delete
        Delete             = 261,
        /// @brief Right
        Right              = 262,
        /// @brief Left
        Left               = 263,
        /// @brief Down
        Down               = 264,
        /// @brief Up
        Up                 = 265,
        /// @brief PageUp
        PageUp             = 266,
        /// @brief PageDown
        PageDown           = 267,
        /// @brief Home
        Home               = 268,
        /// @brief End
        End                = 269,
        /// @brief CapsLock
        CapsLock           = 280,
        /// @brief ScrollLock
        ScrollLock         = 281,
        /// @brief NumLock
        NumLock            = 282,
        /// @brief PrintScreen
        PrintScreen        = 283,
        /// @brief Pause
        Pause              = 284,
        /// @brief F1
        F1                 = 290,
        /// @brief F2
        F2                 = 291,
        /// @brief F3
        F3                 = 292,
        /// @brief F4
        F4                 = 293,
        /// @brief F5
        F5                 = 294,
        /// @brief F6
        F6                 = 295,
        /// @brief F7
        F7                 = 296,
        /// @brief F8
        F8                 = 297,
        /// @brief F9
        F9                 = 298,
        /// @brief F10
        F10                = 299,
        /// @brief F11
        F11                = 300,
        /// @brief F12
        F12                = 301,
        /// @brief F13
        F13                = 302,
        /// @brief F14
        F14                = 303,
        /// @brief F15
        F15                = 304,
        /// @brief F16
        F16                = 305,
        /// @brief F17
        F17                = 306,
        /// @brief F18
        F18                = 307,
        /// @brief F19
        F19                = 308,
        /// @brief F20
        F20                = 309,
        /// @brief F21
        F21                = 310,
        /// @brief F22
        F22                = 311,
        /// @brief F23
        F23                = 312,
        /// @brief F24
        F24                = 313,
        /// @brief F25
        F25                = 314,
        /// @brief Kp0
        Kp0                = 320,
        /// @brief Kp1
        Kp1                = 321,
        /// @brief Kp2
        Kp2                = 322,
        /// @brief Kp3
        Kp3                = 323,
        /// @brief Kp4
        Kp4                = 324,
        /// @brief Kp5
        Kp5                = 325,
        /// @brief Kp6
        Kp6                = 326,
        /// @brief Kp7
        Kp7                = 327,
        /// @brief Kp8
        Kp8                = 328,
        /// @brief Kp9
        Kp9                = 329,
        /// @brief KpDecimal
        KpDecimal          = 330,
        /// @brief KpDivide
        KpDivide           = 331,
        /// @brief KpMultiply
        KpMultiply         = 332,
        /// @brief KpSubtract
        KpSubtract         = 333,
        /// @brief KpAdd
        KpAdd              = 334,
        /// @brief KpEnter
        KpEnter            = 335,
        /// @brief KpEqual
        KpEqual            = 336,
        /// @brief LeftShift
        LeftShift          = 340,
        /// @brief LeftControl
        LeftControl        = 341,
        /// @brief LeftAlt
        LeftAlt            = 342,
        /// @brief LeftSuper
        LeftSuper          = 343,
        /// @brief RightShift
        RightShift         = 344,
        /// @brief RightControl
        RightControl       = 345,
        /// @brief RightAlt
        RightAlt           = 346,
        /// @brief RightSuper
        RightSuper         = 347,
        /// @brief Menu
        Menu               = 348,

        Count              = 355,

        None = 0,
    };

    ENUM_COUNT(Key);

    /// @brief %List of keyboard button states
    enum class KeyStatus : uint8_t
    {
        /// @brief Pressed
        Pressed,
        /// @brief Held down
        Down,
        /// @brief Released
        Release,
        /// @brief Repeated
        Repeat,

        Count
    };

    ENUM_COUNT(KeyStatus);
}
