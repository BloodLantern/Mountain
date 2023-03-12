#include "input.hpp"

#include "renderer.hpp"

Vector2i mountain::Input::MousePosition;
bool mountain::Input::MouseDown[MouseButton_Count];
bool mountain::Input::MouseRelease[MouseButton_Count];
Vector2 mountain::Input::MouseWheel;

bool mountain::Input::KeyDown[Key_Count];
bool mountain::Input::KeyRelease[Key_Count];

bool mountain::Input::ControllerConnected[Controller_Count];
int mountain::Input::ControllerStickCount[Controller_Count];
Vector2* mountain::Input::ControllerStickAxis[Controller_Count];
int mountain::Input::ControllerButtonCount[Controller_Count];
bool* mountain::Input::ControllerButtonStates[Controller_Count];
int mountain::Input::ControllerDirectionalPadCount[Controller_Count];
unsigned char* mountain::Input::ControllerDirectionalPad[Controller_Count];

void MousePositionCallback(GLFWwindow*, double x, double y)
{
    mountain::Input::MousePosition = Vector2i((int) x, (int) y);
}

void MouseButtonCallback(GLFWwindow*, int button, int action, int)
{
    if (action == GLFW_PRESS)
    {
        mountain::Input::MouseDown[button] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        mountain::Input::MouseDown[button] = false;
        mountain::Input::MouseRelease[button] = true;
    }
}

void MouseScrollCallback(GLFWwindow*, double xoffset, double yoffset)
{
    mountain::Input::MouseWheel = Vector2((float) xoffset, (float) yoffset);
}

void KeyCallback(GLFWwindow*, int key, int, int action, int)
{
    // Do not use index -1 in arrays
    if (key == GLFW_KEY_UNKNOWN)
        return;

    if (action == GLFW_PRESS)
    {
        mountain::Input::KeyDown[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        mountain::Input::KeyDown[key] = false;
        mountain::Input::KeyRelease[key] = true;
    }
}

void JoystickCallback(int jid, int event)
{
    if (event == GLFW_CONNECTED)
        mountain::Input::ControllerConnected[jid] = true;
    else if (event == GLFW_DISCONNECTED)
        mountain::Input::ControllerConnected[jid] = false;
}

void mountain::Input::Initialize()
{
    GLFWwindow* window = Renderer::GetWindow();

    glfwSetCursorPosCallback(window, MousePositionCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);

    glfwSetKeyCallback(window, KeyCallback);

    glfwSetJoystickCallback(JoystickCallback);

    for (unsigned char i = 0; i < MouseButton_Count; i++)
    {
        MouseDown[i] = false;
        MouseRelease[i] = false;
    }

    for (unsigned short i = 0; i < Key_Count; i++)
    {
        KeyDown[i] = false;
        KeyRelease[i] = false;
    }

    for (unsigned char i = 0; i < Controller_Count; i++)
    {
        ControllerConnected[i] = false;
        ControllerStickCount[i] = 0;
        ControllerStickAxis[i] = nullptr;
        ControllerButtonStates[i] = nullptr;
        ControllerDirectionalPad[i] = nullptr;
    }
}

void mountain::Input::Update()
{
    for (unsigned char i = 0; i < MouseButton_Count; i++)
        if (MouseRelease[i])
            MouseRelease[i] = false;

    for (unsigned short i = 0; i < Key_Count; i++)
        if (KeyRelease[i])
            KeyRelease[i] = false;

    for (unsigned char i = 0; i < Controller_Count; i++)
        if (ControllerConnected[i])
        {
            {
                // Stick axis
                const float* stickAxis = glfwGetJoystickAxes(i, &ControllerStickCount[i]);

                delete ControllerStickAxis[i];
                ControllerStickAxis[i] = new Vector2[ControllerStickCount[i]];

                for (int j = 0; j < ControllerStickCount[i]; j++)
                    ControllerStickAxis[i][j] = Vector2(stickAxis[j * 2], -stickAxis[j * 2 + 1]);
            }

            {
                // Button states
                const unsigned char* buttonStates = glfwGetJoystickButtons(i, &ControllerButtonCount[i]);

                delete ControllerButtonStates[i];
                ControllerButtonStates[i] = new bool[ControllerButtonCount[i]];

                for (int j = 0; j < ControllerButtonCount[i]; j++)
                    ControllerButtonStates[i][j] = buttonStates[j];
            }

            {
                // Directional pad states
                const unsigned char* directionalPad = glfwGetJoystickHats(i, &ControllerDirectionalPadCount[i]);

                delete ControllerDirectionalPad[i];
                ControllerDirectionalPad[i] = new unsigned char[ControllerDirectionalPadCount[i]];

                for (int j = 0; j < ControllerDirectionalPadCount[i]; j++)
                    ControllerDirectionalPad[i][j] = directionalPad[j];
            }
        }
}
