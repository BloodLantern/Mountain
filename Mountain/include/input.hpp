#pragma once

#include <GLFW/glfw3.h>

#include <vector2i.hpp>

namespace mountain
{
    namespace inputs
    {
        // Volontary include preprocessor inside the namespace.
        #include "input_constants.hpp"
    }
    
    class Input // Static class used to get keyboard, mouse and controller input.
    {
    public:
        static Vector2i MousePosition; // Mouse position Vector2.
        static bool MouseDown[inputs::MouseButton_MaxCount]; // Mouse button down state array.
        static bool MouseRelease[inputs::MouseButton_MaxCount]; // Mouse button release state array.
        static Vector2 MouseWheel; // Mouse wheel offset Vector2. Includes keyboard wheel.

        static bool KeyboardKeyDown[inputs::KeyboardKey_MaxCount]; // Keyboard key down state array.
        static bool KeyboardKeyRelease[inputs::KeyboardKey_MaxCount]; // Keyboard key release state array.

        static unsigned char ControllerConnectedCount; // Controller connected count. Ranges from 0 to 16.
        static bool ControllerConnected[inputs::Controller_MaxCount]; // Controller connected state array.
        static Vector2 ControllerStickAxis[inputs::Controller_MaxCount][inputs::Controller_StickCount]; // Controller stick axis array. Ranges from -1 to 1.
        static float ControllerTriggerAxis[inputs::Controller_MaxCount][inputs::Controller_TriggerCount]; // Controller trigger axis array. Ranges from -1 to 1, -1 being not pressed and 1 being fully pressed.
        static bool ControllerButton[inputs::Controller_MaxCount][inputs::Controller_ButtonCount]; // Controller button states array.
        static unsigned char ControllerDirectionalPad[inputs::Controller_MaxCount]; // Controller directional pad (D-Pad) value array. Values are bits and therefore should be used with bitwise operators.

        // You can't instantiate this class.
        Input() = delete;

        static void Initialize(); // Function used to setup OpenGL callbacks. Automatically called.
        static void Update(); // Function used to update the input states. Automatically called.
    };
}
