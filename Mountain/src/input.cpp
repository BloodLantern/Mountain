#include "input.hpp"

#include "renderer.hpp"

Vector2i mountain::Input::MousePosition;
bool mountain::Input::MouseDown[inputs::MouseButton_MaxCount];
bool mountain::Input::MouseRelease[inputs::MouseButton_MaxCount];
Vector2 mountain::Input::MouseWheel;

bool mountain::Input::KeyboardKeyDown[inputs::KeyboardKey_MaxCount];
bool mountain::Input::KeyboardKeyRelease[inputs::KeyboardKey_MaxCount];

unsigned char mountain::Input::ControllerConnectedCount = 0;
bool mountain::Input::ControllerConnected[inputs::Controller_MaxCount];
Vector2 mountain::Input::ControllerStickAxis[inputs::Controller_MaxCount][inputs::Controller_StickCount];
float mountain::Input::ControllerTriggerAxis[inputs::Controller_MaxCount][inputs::Controller_TriggerCount];
bool mountain::Input::ControllerButton[inputs::Controller_MaxCount][inputs::Controller_ButtonCount];
unsigned char mountain::Input::ControllerDirectionalPad[inputs::Controller_MaxCount];

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
        mountain::Input::KeyboardKeyDown[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        mountain::Input::KeyboardKeyDown[key] = false;
        mountain::Input::KeyboardKeyRelease[key] = true;
    }
}

void JoystickCallback(int jid, int event)
{
    if (event == GLFW_CONNECTED)
    {
        mountain::Input::ControllerConnected[jid] = true;
        mountain::Input::ControllerConnectedCount++;
    }
    else if (event == GLFW_DISCONNECTED)
    {
        mountain::Input::ControllerConnected[jid] = false;
        mountain::Input::ControllerConnectedCount--;
    }
}

void mountain::Input::Initialize()
{
    GLFWwindow* window = Renderer::GetWindow();

    glfwSetCursorPosCallback(window, MousePositionCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);

    glfwSetKeyCallback(window, KeyCallback);

    glfwSetJoystickCallback(JoystickCallback);

    for (unsigned char i = 0; i < inputs::MouseButton_MaxCount; i++)
    {
        MouseDown[i] = false;
        MouseRelease[i] = false;
    }

    for (unsigned short i = 0; i < inputs::KeyboardKey_MaxCount; i++)
    {
        KeyboardKeyDown[i] = false;
        KeyboardKeyRelease[i] = false;
    }

    // Count connected controllers
    for (unsigned char i = 0; i < inputs::Controller_MaxCount; i++)
    {
        const bool present = glfwJoystickPresent(i);
        if (present)
            ControllerConnectedCount++;
        ControllerConnected[i] = present;
    }
}

void mountain::Input::Update()
{
    for (unsigned char i = 0; i < inputs::MouseButton_MaxCount; i++)
        if (MouseRelease[i])
            MouseRelease[i] = false;
    mountain::Input::MouseWheel = 0;

    for (unsigned short i = 0; i < inputs::KeyboardKey_MaxCount; i++)
        if (KeyboardKeyRelease[i])
            KeyboardKeyRelease[i] = false;

    for (unsigned char i = 0; i < inputs::Controller_MaxCount; i++)
        if (ControllerConnected[i])
        {
            {
                // Stick and trigger axis
                int count;
                const float* stickAxis = glfwGetJoystickAxes(i, &count);
                // In case the controller was disconnected and the events weren't polled yet
                if (count == 0)
                    continue;

                ControllerStickAxis[i][0] = Vector2(stickAxis[0], -stickAxis[1]);
                ControllerStickAxis[i][1] = Vector2(stickAxis[2], -stickAxis[5]);

                ControllerTriggerAxis[i][0] = stickAxis[3];
                ControllerTriggerAxis[i][1] = stickAxis[4];
            }

            {
                // Button states
                int count;
                const unsigned char* buttonStates = glfwGetJoystickButtons(i, &count);
                // In case the controller was disconnected and the events weren't polled yet
                if (count == 0)
                    continue;

                ControllerButton[i][inputs::Controller_ButtonSonySquare] = buttonStates[0];
                ControllerButton[i][inputs::Controller_ButtonSonyCross] = buttonStates[1];
                ControllerButton[i][inputs::Controller_ButtonSonyCircle] = buttonStates[2];
                ControllerButton[i][inputs::Controller_ButtonSonyTriangle] = buttonStates[3];
                ControllerButton[i][inputs::Controller_ButtonSonyL1] = buttonStates[4];
                ControllerButton[i][inputs::Controller_ButtonSonyR1] = buttonStates[5];
                ControllerButton[i][inputs::Controller_ButtonSonyL2] = buttonStates[6];
                ControllerButton[i][inputs::Controller_ButtonSonyR2] = buttonStates[7];
                ControllerButton[i][inputs::Controller_ButtonSonyShare] = buttonStates[8];
                ControllerButton[i][inputs::Controller_ButtonSonyOptions] = buttonStates[9];
                ControllerButton[i][inputs::Controller_ButtonSonyL3] = buttonStates[10];
                ControllerButton[i][inputs::Controller_ButtonSonyR3] = buttonStates[11];
                ControllerButton[i][inputs::Controller_ButtonSonyHome] = buttonStates[12];
                ControllerButton[i][inputs::Controller_ButtonSonyTouchPad] = buttonStates[13];
            }

            {
                // Directional pad states
                int count;
                const unsigned char* directionalPad = glfwGetJoystickHats(i, &count);
                // In case the controller was disconnected and the events weren't polled yet
                if (count == 0)
                    continue;

                ControllerDirectionalPad[i] = directionalPad[0];
            }
        }
}
