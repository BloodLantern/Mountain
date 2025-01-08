#include "update_input.h"
#include "gba.h"
#include "structs/game_state.h"
#include "types.h"

#include "GLFW/glfw3.h"

/**
 * @brief 968 | 38 | Updates the input
 * 
 */
void UpdateInput(void)
{
    u16 keys;

    keys = 0;

    if (glfwGetKey(gWindow, GLFW_KEY_LEFT))
        keys |= KEY_LEFT;

    if (glfwGetKey(gWindow, GLFW_KEY_RIGHT))
        keys |= KEY_RIGHT;

    if (glfwGetKey(gWindow, GLFW_KEY_UP))
        keys |= KEY_UP;

    if (glfwGetKey(gWindow, GLFW_KEY_DOWN))
        keys |= KEY_DOWN;

    if (glfwGetKey(gWindow, GLFW_KEY_SPACE))
        keys |= KEY_A;

    if (glfwGetKey(gWindow, GLFW_KEY_TAB))
        keys |= KEY_B;

    if (glfwGetKey(gWindow, GLFW_KEY_ENTER))
        keys |= KEY_START;

    if (glfwGetKey(gWindow, GLFW_KEY_LEFT_ALT))
        keys |= KEY_L;

    if (glfwGetKey(gWindow, GLFW_KEY_R))
        keys |= KEY_R;

    if (glfwGetKey(gWindow, GLFW_KEY_LEFT_CONTROL))
        keys |= KEY_SELECT;

    gChangedInput = keys & ~gPreviousButtonInput;
    gButtonInput = keys;
    gPreviousButtonInput = keys;
}
