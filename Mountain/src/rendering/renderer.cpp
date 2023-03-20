#include "renderer.hpp"

#include <iostream>
#include <cassert>

Vector2 mountain::Renderer::ScreenOrigin = 0;
Vector2i mountain::Renderer::Resolution = TargetResolution;
Vector2i mountain::Renderer::TargetResolution = Vector2i(1920, 1080);
Vector2i mountain::Renderer::WindowPosition;
Vector2i mountain::Renderer::WindowSize;
mountain::Colorf mountain::Renderer::ClearColor = Colorf(0.45f, 0.55f, 0.60f);
GLFWwindow* mountain::Renderer::mWindow = nullptr;
mountain::OpenGLVersion mountain::Renderer::mGlVersion;
Matrix mountain::Renderer::TRS = Matrix::Identity(4);

void mountain::Renderer::Initialize(const char* const windowTitle, const int windowWidth, const int windowHeight, const bool vsync, const OpenGLVersion& glVersion)
{
    mGlVersion = glVersion;

    // Setup GLFW
    glfwSetErrorCallback(
        [](int error, const char* description)
        {
            std::fprintf(stderr, "GLFW error %d: %s\n", error, description);
        }
    );

    if (!glfwInit())
        assert(false && "Failed to initialize GLFW.");

    // GL 3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mGlVersion.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mGlVersion.minor);
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, false);

    // Create window with graphics context
    mWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    assert(mWindow && "Failed to create GLFW window.");

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(vsync); // Enable vsync

    UpdateWindowFields();
}

void mountain::Renderer::PreFrame()
{
    glfwPollEvents();

    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    UpdateWindowFields();

    MakeOpenGLCoordinatesAbsolute(WindowSize.x, WindowSize.y);

    const float trs[16] = {
        TRS[0][0], TRS[0][1], TRS[0][2], TRS[0][3],
        TRS[1][0], TRS[1][1], TRS[1][2], TRS[1][3],
        TRS[2][0], TRS[2][1], TRS[2][2], TRS[2][3],
        TRS[3][0], TRS[3][1], TRS[3][2], TRS[3][3]
    };
    glLoadMatrixf(trs);
    const Vector2 scale = 1 / Resolution / TargetResolution;
    glScalef(scale.x, scale.y, 1);
    glTranslatef(ScreenOrigin.x, ScreenOrigin.y, 0);
}

void mountain::Renderer::PostFrame()
{
    glfwSwapBuffers(mWindow);
}

void mountain::Renderer::Shutdown()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void mountain::Renderer::MakeOpenGLCoordinatesAbsolute(const int windowWidth, const int windowHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mountain::Renderer::UpdateWindowFields()
{
    int windowX, windowY, windowW, windowH;
    glfwGetWindowPos(mWindow, &windowX, &windowY);
    glfwGetWindowSize(mWindow, &windowW, &windowH);
    WindowPosition = Vector2i(windowX, windowY);
    WindowSize = Vector2i(windowW, windowH);
}
