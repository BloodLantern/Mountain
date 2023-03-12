#pragma once

#include <GLFW/glfw3.h>

#include <vector2i.hpp>

namespace mountain
{
    // Volontary include preprocessor inside the namespace.
    #include "input_constants.hpp"

    
    class Input // Static class used to get keyboard, mouse and controller input.
    {
    public:
        static Vector2i MousePosition; // Mouse position Vector2.
        static bool MouseDown[MouseButton_Count]; // Mouse button down state array.
        static bool MouseRelease[MouseButton_Count]; // Mouse button release state array.
        static Vector2 MouseWheel; // Mouse wheel offset Vector2. Includes keyboard wheel.

        static bool KeyDown[Key_Count]; // Keyboard key down state array.
        static bool KeyRelease[Key_Count]; // Keyboard key release state array.

        static bool ControllerConnected[Controller_Count]; // Controller connected state array.
        static int ControllerStickCount[Controller_Count]; // Controller stick count array.
        static Vector2* ControllerStickAxis[Controller_Count]; // Controller stick axis array.
        static int ControllerButtonCount[Controller_Count]; // Controller button count array.
        static bool* ControllerButtonStates[Controller_Count]; // Controller button states array.
        static int ControllerDirectionalPadCount[Controller_Count]; // Controller directional pad (D-Pad) count array.
        static unsigned char* ControllerDirectionalPad[Controller_Count]; // Controller directional pad (D-Pad) states array.

        // You can't instantiate this class.
        Input() = delete;

        static void Initialize(); // Function used to setup OpenGL callbacks. Automatically called.
        static void Update(); // Function used to update the input states. Automatically called.
    };
}
