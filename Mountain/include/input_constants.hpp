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

    constexpr unsigned char MouseButton_Count = GLFW_MOUSE_BUTTON_LAST + 1;
#pragma endregion

#pragma region KeyButtons
    constexpr unsigned short Key_0 = GLFW_KEY_0;
    constexpr unsigned short Key_1 = GLFW_KEY_1;
    constexpr unsigned short Key_2 = GLFW_KEY_2;
    constexpr unsigned short Key_3 = GLFW_KEY_3;
    constexpr unsigned short Key_4 = GLFW_KEY_4;
    constexpr unsigned short Key_5 = GLFW_KEY_5;
    constexpr unsigned short Key_6 = GLFW_KEY_6;
    constexpr unsigned short Key_7 = GLFW_KEY_7;
    constexpr unsigned short Key_8 = GLFW_KEY_8;
    constexpr unsigned short Key_9 = GLFW_KEY_9;

    constexpr unsigned short Key_A = GLFW_KEY_A;
    constexpr unsigned short Key_B = GLFW_KEY_B;
    constexpr unsigned short Key_C = GLFW_KEY_C;
    constexpr unsigned short Key_D = GLFW_KEY_D;
    constexpr unsigned short Key_E = GLFW_KEY_E;
    constexpr unsigned short Key_F = GLFW_KEY_F;
    constexpr unsigned short Key_G = GLFW_KEY_G;
    constexpr unsigned short Key_H = GLFW_KEY_H;
    constexpr unsigned short Key_I = GLFW_KEY_I;
    constexpr unsigned short Key_J = GLFW_KEY_J;
    constexpr unsigned short Key_K = GLFW_KEY_K;
    constexpr unsigned short Key_L = GLFW_KEY_L;
    constexpr unsigned short Key_M = GLFW_KEY_M;
    constexpr unsigned short Key_N = GLFW_KEY_N;
    constexpr unsigned short Key_O = GLFW_KEY_O;
    constexpr unsigned short Key_P = GLFW_KEY_P;
    constexpr unsigned short Key_Q = GLFW_KEY_Q;
    constexpr unsigned short Key_R = GLFW_KEY_R;
    constexpr unsigned short Key_S = GLFW_KEY_S;
    constexpr unsigned short Key_T = GLFW_KEY_T;
    constexpr unsigned short Key_U = GLFW_KEY_U;
    constexpr unsigned short Key_V = GLFW_KEY_V;
    constexpr unsigned short Key_W = GLFW_KEY_W;
    constexpr unsigned short Key_X = GLFW_KEY_X;
    constexpr unsigned short Key_Y = GLFW_KEY_Y;
    constexpr unsigned short Key_Z = GLFW_KEY_Z;

    constexpr unsigned short Key_F1 = GLFW_KEY_F1;
    constexpr unsigned short Key_F2 = GLFW_KEY_F2;
    constexpr unsigned short Key_F3 = GLFW_KEY_F3;
    constexpr unsigned short Key_F4 = GLFW_KEY_F4;
    constexpr unsigned short Key_F5 = GLFW_KEY_F5;
    constexpr unsigned short Key_F6 = GLFW_KEY_F6;
    constexpr unsigned short Key_F7 = GLFW_KEY_F7;
    constexpr unsigned short Key_F8 = GLFW_KEY_F8;
    constexpr unsigned short Key_F9 = GLFW_KEY_F9;
    constexpr unsigned short Key_F10 = GLFW_KEY_F10;
    constexpr unsigned short Key_F11 = GLFW_KEY_F11;
    constexpr unsigned short Key_F12 = GLFW_KEY_F12;
    constexpr unsigned short Key_F13 = GLFW_KEY_F13;
    constexpr unsigned short Key_F14 = GLFW_KEY_F14;
    constexpr unsigned short Key_F15 = GLFW_KEY_F15;
    constexpr unsigned short Key_F16 = GLFW_KEY_F16;
    constexpr unsigned short Key_F17 = GLFW_KEY_F17;
    constexpr unsigned short Key_F18 = GLFW_KEY_F18;
    constexpr unsigned short Key_F19 = GLFW_KEY_F19;
    constexpr unsigned short Key_F20 = GLFW_KEY_F20;
    constexpr unsigned short Key_F21 = GLFW_KEY_F21;
    constexpr unsigned short Key_F22 = GLFW_KEY_F22;
    constexpr unsigned short Key_F23 = GLFW_KEY_F23;
    constexpr unsigned short Key_F24 = GLFW_KEY_F24;
    constexpr unsigned short Key_F25 = GLFW_KEY_F25;

    constexpr unsigned short Key_Apostrophe = GLFW_KEY_APOSTROPHE;
    constexpr unsigned short Key_Backslash = GLFW_KEY_BACKSLASH;
    constexpr unsigned short Key_Backspace = GLFW_KEY_BACKSPACE;
    constexpr unsigned short Key_CapsLock = GLFW_KEY_CAPS_LOCK;
    constexpr unsigned short Key_Comma = GLFW_KEY_COMMA;
    constexpr unsigned short Key_Delete = GLFW_KEY_DELETE;
    constexpr unsigned short Key_End = GLFW_KEY_END;
    constexpr unsigned short Key_Enter = GLFW_KEY_ENTER;
    constexpr unsigned short Key_Equal = GLFW_KEY_EQUAL;
    constexpr unsigned short Key_Escape = GLFW_KEY_ESCAPE;
    constexpr unsigned short Key_GraveAccent = GLFW_KEY_GRAVE_ACCENT;
    constexpr unsigned short Key_Home = GLFW_KEY_HOME;
    constexpr unsigned short Key_Insert = GLFW_KEY_INSERT;
    constexpr unsigned short Key_LeftBracket = GLFW_KEY_LEFT_BRACKET;
    constexpr unsigned short Key_Menu = GLFW_KEY_MENU;
    constexpr unsigned short Key_Minus = GLFW_KEY_MINUS;
    constexpr unsigned short Key_PageDown = GLFW_KEY_PAGE_DOWN;
    constexpr unsigned short Key_PageUp = GLFW_KEY_PAGE_UP;
    constexpr unsigned short Key_Pause = GLFW_KEY_PAUSE;
    constexpr unsigned short Key_Period = GLFW_KEY_PERIOD;
    constexpr unsigned short Key_PrintScreen = GLFW_KEY_PRINT_SCREEN;
    constexpr unsigned short Key_RightBracket = GLFW_KEY_RIGHT_BRACKET;
    constexpr unsigned short Key_ScrollLock = GLFW_KEY_SCROLL_LOCK;
    constexpr unsigned short Key_Semicolon = GLFW_KEY_SEMICOLON;
    constexpr unsigned short Key_Slash = GLFW_KEY_SLASH;
    constexpr unsigned short Key_Space = GLFW_KEY_SPACE;
    constexpr unsigned short Key_Tab = GLFW_KEY_TAB;
    constexpr unsigned short Key_World1 = GLFW_KEY_WORLD_1;
    constexpr unsigned short Key_World2 = GLFW_KEY_WORLD_2;

    constexpr unsigned short Key_LeftShift = GLFW_KEY_LEFT_SHIFT;
    constexpr unsigned short Key_RightShift = GLFW_KEY_RIGHT_SHIFT;
    constexpr unsigned short Key_LeftControl = GLFW_KEY_LEFT_CONTROL;
    constexpr unsigned short Key_RightControl = GLFW_KEY_RIGHT_CONTROL;
    constexpr unsigned short Key_LeftAlt = GLFW_KEY_LEFT_ALT;
    constexpr unsigned short Key_RightAlt = GLFW_KEY_RIGHT_ALT;
    constexpr unsigned short Key_LeftSuper = GLFW_KEY_LEFT_SUPER;
    constexpr unsigned short Key_RightSuper = GLFW_KEY_RIGHT_SUPER;

    constexpr unsigned short Key_KeyPad0 = GLFW_KEY_KP_0;
    constexpr unsigned short Key_KeyPad1 = GLFW_KEY_KP_1;
    constexpr unsigned short Key_KeyPad2 = GLFW_KEY_KP_2;
    constexpr unsigned short Key_KeyPad3 = GLFW_KEY_KP_3;
    constexpr unsigned short Key_KeyPad4 = GLFW_KEY_KP_4;
    constexpr unsigned short Key_KeyPad5 = GLFW_KEY_KP_5;
    constexpr unsigned short Key_KeyPad6 = GLFW_KEY_KP_6;
    constexpr unsigned short Key_KeyPad7 = GLFW_KEY_KP_7;
    constexpr unsigned short Key_KeyPad8 = GLFW_KEY_KP_8;
    constexpr unsigned short Key_KeyPad9 = GLFW_KEY_KP_9;
    constexpr unsigned short Key_NumLock = GLFW_KEY_NUM_LOCK;
    constexpr unsigned short Key_KeyPadDivide = GLFW_KEY_KP_DIVIDE;
    constexpr unsigned short Key_KeyPadMultiply = GLFW_KEY_KP_MULTIPLY;
    constexpr unsigned short Key_KeyPadSubstract = GLFW_KEY_KP_SUBTRACT;
    constexpr unsigned short Key_KeyPadAdd = GLFW_KEY_KP_ADD;
    constexpr unsigned short Key_KeyPadEnter = GLFW_KEY_KP_ENTER;
    constexpr unsigned short Key_KeyPadDecimal = GLFW_KEY_KP_DECIMAL;

    constexpr unsigned short Key_Left = GLFW_KEY_LEFT;
    constexpr unsigned short Key_Right = GLFW_KEY_RIGHT;
    constexpr unsigned short Key_Up = GLFW_KEY_UP;
    constexpr unsigned short Key_Down = GLFW_KEY_DOWN;

    constexpr unsigned short Key_Count = GLFW_KEY_LAST + 1;
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

    constexpr unsigned char Controller_StickCount = 2;
    constexpr unsigned char Controller_ButtonCount = 9;
    constexpr unsigned char Controller_DirectionalPadCount = 1;

    constexpr unsigned char Controller_Count = GLFW_JOYSTICK_LAST + 1;
#pragma endregion
