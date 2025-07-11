#pragma once

#include "Mountain/Core.hpp"

/// @file KeyboardInput.hpp
/// @brief Defines enumerators related to keyboard input

namespace Mountain
{
    /// @brief %List of keyboard buttons
    enum class Key : uint16_t
    {
        /// @brief '\r'
        Return = 0x0000000du,
        /// @brief '\x1B'
        Escape = 0x0000001bu,
        /// @brief '\b'
        Backspace = 0x00000008u,
        /// @brief '\t'
        Tab = 0x00000009u,
        /// @brief ' '
        Space = 0x00000020u,
        /// @brief '!'
        Exclaim = 0x00000021u,
        /// @brief '"'
        DblApostrophe = 0x00000022u,
        /// @brief '#'
        Hash = 0x00000023u,
        /// @brief '$'
        Dollar = 0x00000024u,
        /// @brief '%'
        Percent = 0x00000025u,
        /// @brief '&'
        Ampersand = 0x00000026u,
        /// @brief '\''
        Apostrophe = 0x00000027u,
        /// @brief '('
        LeftParen = 0x00000028u,
        /// @brief ')'
        RightParen = 0x00000029u,
        /// @brief '*'
        Asterisk = 0x0000002au,
        /// @brief '+'
        Plus = 0x0000002bu,
        /// @brief ','
        Comma = 0x0000002cu,
        /// @brief '-'
        Minus = 0x0000002du,
        /// @brief '.'
        Period = 0x0000002eu,
        /// @brief '/'
        Slash = 0x0000002fu,
        /// @brief '0'
        Zero = 0x00000030u,
        /// @brief '1'
        One = 0x00000031u,
        /// @brief '2'
        Two = 0x00000032u,
        /// @brief '3'
        Three = 0x00000033u,
        /// @brief '4'
        Four = 0x00000034u,
        /// @brief '5'
        Five = 0x00000035u,
        /// @brief '6'
        Six = 0x00000036u,
        /// @brief '7'
        Seven = 0x00000037u,
        /// @brief '8'
        Eight = 0x00000038u,
        /// @brief '9'
        Nine = 0x00000039u,
        /// @brief ':'
        Colon = 0x0000003au,
        /// @brief ';'
        Semicolon = 0x0000003bu,
        /// @brief '<'
        Less = 0x0000003cu,
        /// @brief '='
        Equals = 0x0000003du,
        /// @brief '>'
        Greater = 0x0000003eu,
        /// @brief '?'
        Question = 0x0000003fu,
        /// @brief '@'
        At = 0x00000040u,
        /// @brief '['
        LeftBracket = 0x0000005bu,
        /// @brief '\\'
        Backslash = 0x0000005cu,
        /// @brief ']'
        RightBracket = 0x0000005du,
        /// @brief '^'
        Caret = 0x0000005eu,
        /// @brief '_'
        Underscore = 0x0000005fu,
        /// @brief '`'
        Grave = 0x00000060u,
        /// @brief 'a'
        A = 0x00000061u,
        /// @brief 'b'
        B = 0x00000062u,
        /// @brief 'c'
        C = 0x00000063u,
        /// @brief 'd'
        D = 0x00000064u,
        /// @brief 'e'
        E = 0x00000065u,
        /// @brief 'f'
        F = 0x00000066u,
        /// @brief 'g'
        G = 0x00000067u,
        /// @brief 'h'
        H = 0x00000068u,
        /// @brief 'i'
        I = 0x00000069u,
        /// @brief 'j'
        J = 0x0000006au,
        /// @brief 'k'
        K = 0x0000006bu,
        /// @brief 'l'
        L = 0x0000006cu,
        /// @brief 'm'
        M = 0x0000006du,
        /// @brief 'n'
        N = 0x0000006eu,
        /// @brief 'o'
        O = 0x0000006fu,
        /// @brief 'p'
        P = 0x00000070u,
        /// @brief 'q'
        Q = 0x00000071u,
        /// @brief 'r'
        R = 0x00000072u,
        /// @brief 's'
        S = 0x00000073u,
        /// @brief 't'
        T = 0x00000074u,
        /// @brief 'u'
        U = 0x00000075u,
        /// @brief 'v'
        V = 0x00000076u,
        /// @brief 'w'
        W = 0x00000077u,
        /// @brief 'x'
        X = 0x00000078u,
        /// @brief 'y'
        Y = 0x00000079u,
        /// @brief 'z'
        Z = 0x0000007au,
        /// @brief '{'
        LeftBrace = 0x0000007bu,
        /// @brief '|'
        Pipe = 0x0000007cu,
        /// @brief '}'
        RightBrace = 0x0000007du,
        /// @brief '~'
        Tilde = 0x0000007eu,
        /// @brief '\x7F'
        Delete = 0x0000007fu,

        NormalEnd = Delete,

        /* Scancode keys */

        Capslock,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        PrintScreen,
        ScrollLock,
        Pause,
        Insert,
        Home,
        Pageup,
        End,
        Pagedown,
        Right,
        Left,
        Down,
        Up,
        NumLockClear,
        KpDivide,
        KpMultiply,
        KpMinus,
        KpPlus,
        KpEnter,
        Kp1,
        Kp2,
        Kp3,
        Kp4,
        Kp5,
        Kp6,
        Kp7,
        Kp8,
        Kp9,
        Kp0,
        KpPeriod,
        Application,
        Power,
        KpEquals,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        Execute,
        Help,
        Menu,
        Select,
        Stop,
        Again,
        Undo,
        Cut,
        Copy,
        Paste,
        Find,
        Mute,
        VolumeUp,
        VolumeDown,
        KpComma,
        KpEqualsAs400,
        AlterAsE,
        SysReq,
        Cancel,
        Clear,
        Prior,
        Return2,
        Separator,
        Out,
        Oper,
        ClearAgain,
        CrSel,
        ExSel,
        Kp00,
        Kp000,
        ThousandsSeparator,
        DecimalSeparator,
        CurrencyUnit,
        CurrencySubUnit,
        KpLeftParen,
        KpRightParen,
        KpLeftBrace,
        KpRightBrace,
        KpTab,
        KpBackspace,
        KpA,
        KpB,
        KpC,
        KpD,
        KpE,
        KpF,
        KpXor,
        KpPower,
        KpPercent,
        KpLess,
        KpGreater,
        KpAmpersand,
        KpDblAmpersand,
        KpVerticalBar,
        KpDblVerticalBar,
        KpColon,
        KpHash,
        KpSpace,
        KpAt,
        KpExclam,
        KpMemStore,
        KpMemRecall,
        KpMemClear,
        KpMemAdd,
        KpMemSubtract,
        KpMemMultiply,
        KpMemDivide,
        KpPlusMinus,
        KpClear,
        KpClearEntry,
        KpBinary,
        KpOctal,
        KpDecimal,
        KpHexadecimal,
        LeftControl,
        LeftShift,
        LeftAlt,
        LeftGui,
        RightControl,
        RightShift,
        RightAlt,
        RightGui,
        Mode,
        Sleep,
        Wake,
        ChannelIncrement,
        ChannelDecrement,
        MediaPlay,
        MediaPause,
        MediaRecord,
        MediaFastForward,
        MediaRewind,
        MediaNextTrack,
        MediaPreviousTrack,
        MediaStop,
        MediaEject,
        MediaPlayPause,
        MediaSelect,
        AcNew,
        AcOpen,
        AcClose,
        AcExit,
        AcSave,
        AcPrint,
        AcProperties,
        AcSearch,
        AcHome,
        AcBack,
        AcForward,
        AcStop,
        AcRefresh,
        AcBookmarks,
        SoftLeft,
        SoftRight,
        Call,
        EndCall,

        None,

        Count
    };

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
        Repeat
    };

    enum class KeyAction : uint8_t
    {
        Release,
        Press,
        Repeat
    };
}
