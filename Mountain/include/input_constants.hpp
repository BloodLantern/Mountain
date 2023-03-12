#pragma once

#include <GLFW/glfw3.h>

#pragma region MouseButtons
    constexpr unsigned char MouseButton_1 = GLFW_MOUSE_BUTTON_1;
    constexpr unsigned char MouseButton_2 = GLFW_MOUSE_BUTTON_2;
    constexpr unsigned char MouseButton_3 = GLFW_MOUSE_BUTTON_3;
    constexpr unsigned char MouseButton_4 = GLFW_MOUSE_BUTTON_4;
    constexpr unsigned char MouseButton_5 = GLFW_MOUSE_BUTTON_5;
    constexpr unsigned char MouseButton_6 = GLFW_MOUSE_BUTTON_6;
    constexpr unsigned char MouseButton_7 = GLFW_MOUSE_BUTTON_7;
    constexpr unsigned char MouseButton_8 = GLFW_MOUSE_BUTTON_8;

    constexpr unsigned char MouseButton_Left = GLFW_MOUSE_BUTTON_LEFT;
    constexpr unsigned char MouseButton_Right = GLFW_MOUSE_BUTTON_RIGHT;
    constexpr unsigned char MouseButton_Middle = GLFW_MOUSE_BUTTON_MIDDLE;

    constexpr unsigned char MouseButton_MaxCount = GLFW_MOUSE_BUTTON_LAST + 1;
#pragma endregion

#pragma region KeyButtons
    constexpr unsigned short KeyboardKey_0 = GLFW_KEY_0;
    constexpr unsigned short KeyboardKey_1 = GLFW_KEY_1;
    constexpr unsigned short KeyboardKey_2 = GLFW_KEY_2;
    constexpr unsigned short KeyboardKey_3 = GLFW_KEY_3;
    constexpr unsigned short KeyboardKey_4 = GLFW_KEY_4;
    constexpr unsigned short KeyboardKey_5 = GLFW_KEY_5;
    constexpr unsigned short KeyboardKey_6 = GLFW_KEY_6;
    constexpr unsigned short KeyboardKey_7 = GLFW_KEY_7;
    constexpr unsigned short KeyboardKey_8 = GLFW_KEY_8;
    constexpr unsigned short KeyboardKey_9 = GLFW_KEY_9;

    constexpr unsigned short KeyboardKey_A = GLFW_KEY_A;
    constexpr unsigned short KeyboardKey_B = GLFW_KEY_B;
    constexpr unsigned short KeyboardKey_C = GLFW_KEY_C;
    constexpr unsigned short KeyboardKey_D = GLFW_KEY_D;
    constexpr unsigned short KeyboardKey_E = GLFW_KEY_E;
    constexpr unsigned short KeyboardKey_F = GLFW_KEY_F;
    constexpr unsigned short KeyboardKey_G = GLFW_KEY_G;
    constexpr unsigned short KeyboardKey_H = GLFW_KEY_H;
    constexpr unsigned short KeyboardKey_I = GLFW_KEY_I;
    constexpr unsigned short KeyboardKey_J = GLFW_KEY_J;
    constexpr unsigned short KeyboardKey_K = GLFW_KEY_K;
    constexpr unsigned short KeyboardKey_L = GLFW_KEY_L;
    constexpr unsigned short KeyboardKey_M = GLFW_KEY_M;
    constexpr unsigned short KeyboardKey_N = GLFW_KEY_N;
    constexpr unsigned short KeyboardKey_O = GLFW_KEY_O;
    constexpr unsigned short KeyboardKey_P = GLFW_KEY_P;
    constexpr unsigned short KeyboardKey_Q = GLFW_KEY_Q;
    constexpr unsigned short KeyboardKey_R = GLFW_KEY_R;
    constexpr unsigned short KeyboardKey_S = GLFW_KEY_S;
    constexpr unsigned short KeyboardKey_T = GLFW_KEY_T;
    constexpr unsigned short KeyboardKey_U = GLFW_KEY_U;
    constexpr unsigned short KeyboardKey_V = GLFW_KEY_V;
    constexpr unsigned short KeyboardKey_W = GLFW_KEY_W;
    constexpr unsigned short KeyboardKey_X = GLFW_KEY_X;
    constexpr unsigned short KeyboardKey_Y = GLFW_KEY_Y;
    constexpr unsigned short KeyboardKey_Z = GLFW_KEY_Z;

    constexpr unsigned short KeyboardKey_F1 = GLFW_KEY_F1;
    constexpr unsigned short KeyboardKey_F2 = GLFW_KEY_F2;
    constexpr unsigned short KeyboardKey_F3 = GLFW_KEY_F3;
    constexpr unsigned short KeyboardKey_F4 = GLFW_KEY_F4;
    constexpr unsigned short KeyboardKey_F5 = GLFW_KEY_F5;
    constexpr unsigned short KeyboardKey_F6 = GLFW_KEY_F6;
    constexpr unsigned short KeyboardKey_F7 = GLFW_KEY_F7;
    constexpr unsigned short KeyboardKey_F8 = GLFW_KEY_F8;
    constexpr unsigned short KeyboardKey_F9 = GLFW_KEY_F9;
    constexpr unsigned short KeyboardKey_F10 = GLFW_KEY_F10;
    constexpr unsigned short KeyboardKey_F11 = GLFW_KEY_F11;
    constexpr unsigned short KeyboardKey_F12 = GLFW_KEY_F12;
    constexpr unsigned short KeyboardKey_F13 = GLFW_KEY_F13;
    constexpr unsigned short KeyboardKey_F14 = GLFW_KEY_F14;
    constexpr unsigned short KeyboardKey_F15 = GLFW_KEY_F15;
    constexpr unsigned short KeyboardKey_F16 = GLFW_KEY_F16;
    constexpr unsigned short KeyboardKey_F17 = GLFW_KEY_F17;
    constexpr unsigned short KeyboardKey_F18 = GLFW_KEY_F18;
    constexpr unsigned short KeyboardKey_F19 = GLFW_KEY_F19;
    constexpr unsigned short KeyboardKey_F20 = GLFW_KEY_F20;
    constexpr unsigned short KeyboardKey_F21 = GLFW_KEY_F21;
    constexpr unsigned short KeyboardKey_F22 = GLFW_KEY_F22;
    constexpr unsigned short KeyboardKey_F23 = GLFW_KEY_F23;
    constexpr unsigned short KeyboardKey_F24 = GLFW_KEY_F24;
    constexpr unsigned short KeyboardKey_F25 = GLFW_KEY_F25;

    constexpr unsigned short KeyboardKey_Apostrophe = GLFW_KEY_APOSTROPHE;
    constexpr unsigned short KeyboardKey_Backslash = GLFW_KEY_BACKSLASH;
    constexpr unsigned short KeyboardKey_Backspace = GLFW_KEY_BACKSPACE;
    constexpr unsigned short KeyboardKey_CapsLock = GLFW_KEY_CAPS_LOCK;
    constexpr unsigned short KeyboardKey_Comma = GLFW_KEY_COMMA;
    constexpr unsigned short KeyboardKey_Delete = GLFW_KEY_DELETE;
    constexpr unsigned short KeyboardKey_End = GLFW_KEY_END;
    constexpr unsigned short KeyboardKey_Enter = GLFW_KEY_ENTER;
    constexpr unsigned short KeyboardKey_Equal = GLFW_KEY_EQUAL;
    constexpr unsigned short KeyboardKey_Escape = GLFW_KEY_ESCAPE;
    constexpr unsigned short KeyboardKey_GraveAccent = GLFW_KEY_GRAVE_ACCENT;
    constexpr unsigned short KeyboardKey_Home = GLFW_KEY_HOME;
    constexpr unsigned short KeyboardKey_Insert = GLFW_KEY_INSERT;
    constexpr unsigned short KeyboardKey_LeftBracket = GLFW_KEY_LEFT_BRACKET;
    constexpr unsigned short KeyboardKey_Menu = GLFW_KEY_MENU;
    constexpr unsigned short KeyboardKey_Minus = GLFW_KEY_MINUS;
    constexpr unsigned short KeyboardKey_PageDown = GLFW_KEY_PAGE_DOWN;
    constexpr unsigned short KeyboardKey_PageUp = GLFW_KEY_PAGE_UP;
    constexpr unsigned short KeyboardKey_Pause = GLFW_KEY_PAUSE;
    constexpr unsigned short KeyboardKey_Period = GLFW_KEY_PERIOD;
    constexpr unsigned short KeyboardKey_PrintScreen = GLFW_KEY_PRINT_SCREEN;
    constexpr unsigned short KeyboardKey_RightBracket = GLFW_KEY_RIGHT_BRACKET;
    constexpr unsigned short KeyboardKey_ScrollLock = GLFW_KEY_SCROLL_LOCK;
    constexpr unsigned short KeyboardKey_Semicolon = GLFW_KEY_SEMICOLON;
    constexpr unsigned short KeyboardKey_Slash = GLFW_KEY_SLASH;
    constexpr unsigned short KeyboardKey_Space = GLFW_KEY_SPACE;
    constexpr unsigned short KeyboardKey_Tab = GLFW_KEY_TAB;
    constexpr unsigned short KeyboardKey_World1 = GLFW_KEY_WORLD_1;
    constexpr unsigned short KeyboardKey_World2 = GLFW_KEY_WORLD_2;

    constexpr unsigned short KeyboardKey_LeftShift = GLFW_KEY_LEFT_SHIFT;
    constexpr unsigned short KeyboardKey_RightShift = GLFW_KEY_RIGHT_SHIFT;
    constexpr unsigned short KeyboardKey_LeftControl = GLFW_KEY_LEFT_CONTROL;
    constexpr unsigned short KeyboardKey_RightControl = GLFW_KEY_RIGHT_CONTROL;
    constexpr unsigned short KeyboardKey_LeftAlt = GLFW_KEY_LEFT_ALT;
    constexpr unsigned short KeyboardKey_RightAlt = GLFW_KEY_RIGHT_ALT;
    constexpr unsigned short KeyboardKey_LeftSuper = GLFW_KEY_LEFT_SUPER;
    constexpr unsigned short KeyboardKey_RightSuper = GLFW_KEY_RIGHT_SUPER;

    constexpr unsigned short KeyboardKey_NumPad0 = GLFW_KEY_KP_0;
    constexpr unsigned short KeyboardKey_NumPad1 = GLFW_KEY_KP_1;
    constexpr unsigned short KeyboardKey_NumPad2 = GLFW_KEY_KP_2;
    constexpr unsigned short KeyboardKey_NumPad3 = GLFW_KEY_KP_3;
    constexpr unsigned short KeyboardKey_NumPad4 = GLFW_KEY_KP_4;
    constexpr unsigned short KeyboardKey_NumPad5 = GLFW_KEY_KP_5;
    constexpr unsigned short KeyboardKey_NumPad6 = GLFW_KEY_KP_6;
    constexpr unsigned short KeyboardKey_NumPad7 = GLFW_KEY_KP_7;
    constexpr unsigned short KeyboardKey_NumPad8 = GLFW_KEY_KP_8;
    constexpr unsigned short KeyboardKey_NumPad9 = GLFW_KEY_KP_9;
    constexpr unsigned short KeyboardKey_NumLock = GLFW_KEY_NUM_LOCK;
    constexpr unsigned short KeyboardKey_NumPadDivide = GLFW_KEY_KP_DIVIDE;
    constexpr unsigned short KeyboardKey_NumPadMultiply = GLFW_KEY_KP_MULTIPLY;
    constexpr unsigned short KeyboardKey_NumPadSubstract = GLFW_KEY_KP_SUBTRACT;
    constexpr unsigned short KeyboardKey_NumPadAdd = GLFW_KEY_KP_ADD;
    constexpr unsigned short KeyboardKey_NumPadEnter = GLFW_KEY_KP_ENTER;
    constexpr unsigned short KeyboardKey_NumPadDecimal = GLFW_KEY_KP_DECIMAL;

    constexpr unsigned short KeyboardKey_Left = GLFW_KEY_LEFT;
    constexpr unsigned short KeyboardKey_Right = GLFW_KEY_RIGHT;
    constexpr unsigned short KeyboardKey_Up = GLFW_KEY_UP;
    constexpr unsigned short KeyboardKey_Down = GLFW_KEY_DOWN;

    constexpr unsigned short KeyboardKey_MaxCount = GLFW_KEY_LAST + 1;
#pragma endregion

#pragma region Controller
    constexpr unsigned char Controller_1 = GLFW_JOYSTICK_1;
    constexpr unsigned char Controller_2 = GLFW_JOYSTICK_2;
    constexpr unsigned char Controller_3 = GLFW_JOYSTICK_3;
    constexpr unsigned char Controller_4 = GLFW_JOYSTICK_4;
    constexpr unsigned char Controller_5 = GLFW_JOYSTICK_5;
    constexpr unsigned char Controller_6 = GLFW_JOYSTICK_6;
    constexpr unsigned char Controller_7 = GLFW_JOYSTICK_7;
    constexpr unsigned char Controller_8 = GLFW_JOYSTICK_8;
    constexpr unsigned char Controller_9 = GLFW_JOYSTICK_9;
    constexpr unsigned char Controller_10 = GLFW_JOYSTICK_10;
    constexpr unsigned char Controller_11 = GLFW_JOYSTICK_11;
    constexpr unsigned char Controller_12 = GLFW_JOYSTICK_12;
    constexpr unsigned char Controller_13 = GLFW_JOYSTICK_13;
    constexpr unsigned char Controller_14 = GLFW_JOYSTICK_14;
    constexpr unsigned char Controller_15 = GLFW_JOYSTICK_15;
    constexpr unsigned char Controller_16 = GLFW_JOYSTICK_16;

    constexpr unsigned char Controller_StickLeft = 0;
    constexpr unsigned char Controller_StickRight = 1;

    constexpr unsigned char Controller_TriggerLeft = 0;
    constexpr unsigned char Controller_TriggerRight = 1;

    #pragma region ControllerButtons
        constexpr unsigned char Controller_ButtonSonySquare = 0;
        constexpr unsigned char Controller_ButtonSonyCross = 1;
        constexpr unsigned char Controller_ButtonSonyCircle = 2;
        constexpr unsigned char Controller_ButtonSonyTriangle = 3;
        constexpr unsigned char Controller_ButtonSonyL1 = 4; // Button above the left trigger.
        constexpr unsigned char Controller_ButtonSonyR1 = 5; // Button above the right trigger.
        constexpr unsigned char Controller_ButtonSonyL2 = 6; // Left trigger. True when the trigger axis is greater than -1 (default value).
        constexpr unsigned char Controller_ButtonSonyR2 = 7; // Right trigger. True when the trigger axis is greater than -1 (default value).
        constexpr unsigned char Controller_ButtonSonyShare = 8;
        constexpr unsigned char Controller_ButtonSonyOptions = 9;
        constexpr unsigned char Controller_ButtonSonyHome = 10; // Sony button.
        constexpr unsigned char Controller_ButtonSonyTouchPad = 11; // Touch pad press.
        constexpr unsigned char Controller_ButtonSonyL3 = 12; // Left stick press.
        constexpr unsigned char Controller_ButtonSonyR3 = 13; // Right stick press.
        
        constexpr unsigned char Controller_ButtonMicrosoftX = Controller_ButtonSonySquare;
        constexpr unsigned char Controller_ButtonMicrosoftA = Controller_ButtonSonyCross;
        constexpr unsigned char Controller_ButtonMicrosoftB = Controller_ButtonSonyCircle;
        constexpr unsigned char Controller_ButtonMicrosoftY = Controller_ButtonSonyTriangle;
        constexpr unsigned char Controller_ButtonMicrosoftLeftBumper = Controller_ButtonSonyL1; // Button above the left trigger.
        constexpr unsigned char Controller_ButtonMicrosoftRightBumper = Controller_ButtonSonyR1; // Button above the right trigger.
        constexpr unsigned char Controller_ButtonMicrosoftLeftTrigger = Controller_ButtonSonyL2; // Left trigger. True when the trigger axis is greater than -1 (default value).
        constexpr unsigned char Controller_ButtonMicrosoftRightTrigger = Controller_ButtonSonyR2; // Right trigger. True when the trigger axis is greater than -1 (default value).
        constexpr unsigned char Controller_ButtonMicrosoftBack = Controller_ButtonSonyShare;
        constexpr unsigned char Controller_ButtonMicrosoftStart = Controller_ButtonSonyOptions;
        constexpr unsigned char Controller_ButtonMicrosoftGuide = Controller_ButtonSonyHome; // Microsoft button.
        constexpr unsigned char Controller_ButtonMicrosoftLeftStick = Controller_ButtonSonyL3; // Left stick press.
        constexpr unsigned char Controller_ButtonMicrosoftRightStick = Controller_ButtonSonyR3; // Right stick press.
        
        constexpr unsigned char Controller_ButtonNintendoY = Controller_ButtonSonySquare;
        constexpr unsigned char Controller_ButtonNintendoB = Controller_ButtonSonyCross;
        constexpr unsigned char Controller_ButtonNintendoA = Controller_ButtonSonyCircle;
        constexpr unsigned char Controller_ButtonNintendoX = Controller_ButtonSonyTriangle;
        constexpr unsigned char Controller_ButtonNintendoL = Controller_ButtonSonyL1; // Button above the left trigger.
        constexpr unsigned char Controller_ButtonNintendoR = Controller_ButtonSonyR1; // Button above the right trigger.
        constexpr unsigned char Controller_ButtonNintendoZL = Controller_ButtonSonyL2; // Left trigger. True when the trigger axis is greater than -1 (default value).
        constexpr unsigned char Controller_ButtonNintendoZR = Controller_ButtonSonyR2; // Right trigger. True when the trigger axis is greater than -1 (default value).
        constexpr unsigned char Controller_ButtonNintendoMinus = Controller_ButtonSonyShare;
        constexpr unsigned char Controller_ButtonNintendoPlus = Controller_ButtonSonyOptions;
        constexpr unsigned char Controller_ButtonNintendoHome = Controller_ButtonSonyHome;
        constexpr unsigned char Controller_ButtonNintendoCapture = Controller_ButtonSonyTouchPad; // Screenshot button.
        constexpr unsigned char Controller_ButtonNintendoLeftStick = Controller_ButtonSonyL3; // Left stick press.
        constexpr unsigned char Controller_ButtonNintendoRightStick = Controller_ButtonSonyR3; // Right stick press.
    #pragma endregion

    constexpr unsigned char Controller_DirectionalPadDefault = GLFW_HAT_CENTERED; // Meaning that the directional pad is centered and therefore unused.
    constexpr unsigned char Controller_DirectionalPadUp = GLFW_HAT_UP;
    constexpr unsigned char Controller_DirectionalPadRight = GLFW_HAT_RIGHT;
    constexpr unsigned char Controller_DirectionalPadDown = GLFW_HAT_DOWN;
    constexpr unsigned char Controller_DirectionalPadLeft = GLFW_HAT_LEFT;
    constexpr unsigned char Controller_DirectionalPadRightUp = GLFW_HAT_RIGHT_UP;
    constexpr unsigned char Controller_DirectionalPadRightDown = GLFW_HAT_RIGHT_DOWN;
    constexpr unsigned char Controller_DirectionalPadLeftUp = GLFW_HAT_LEFT_UP;
    constexpr unsigned char Controller_DirectionalPadLeftDown = GLFW_HAT_LEFT_DOWN;

    constexpr unsigned char Controller_StickCount = 2;
    constexpr unsigned char Controller_TriggerCount = 2;
    constexpr unsigned char Controller_ButtonCount = 14;

    constexpr unsigned char Controller_MaxCount = GLFW_JOYSTICK_LAST + 1;
#pragma endregion
