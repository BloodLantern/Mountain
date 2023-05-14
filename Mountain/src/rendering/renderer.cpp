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
Matrix4x4 mountain::Renderer::Camera = Matrix4x4::Identity();

void mountain::Renderer::Initialize(const char* const windowTitle, const int windowWidth, const int windowHeight, const bool vsync, const OpenGLVersion& glVersion)
{
    mGlVersion = glVersion;

    // Setup GLFW
    glfwSetErrorCallback(
        [](int error, const char* description)
        {
            std::cerr << "GLFW error " << error << ": " << description << std::endl;
        }
    );

    if (!glfwInit())
        assert(false && "Failed to initialize GLFW.");

    // GL 3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mGlVersion.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mGlVersion.minor);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, false);

    // Create window with graphics context
    mWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    assert(mWindow && "Failed to create GLFW window.");

    glfwMakeContextCurrent(mWindow);
    // Enable vsync
    glfwSwapInterval(vsync);

    // Enable transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    UpdateWindowFields();
}

void mountain::Renderer::PreFrame()
{
    glfwPollEvents();

    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    UpdateWindowFields();

    MakeOpenGLCoordinatesAbsolute(WindowSize.x, WindowSize.y);

    UpdateModelViewMatrix();
}

void mountain::Renderer::PostFrame()
{
    glFlush();
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
}

void mountain::Renderer::UpdateModelViewMatrix()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Matrix4x4 temp = Camera;
    const Vector2 resolutionMultiplier = 1 / (Resolution / TargetResolution);
    temp[0][3] *= resolutionMultiplier.x;
    temp[1][3] *= resolutionMultiplier.y;
    temp.Transpose();
    glLoadMatrixf(&temp[0][0]);
    const Vector2 scale = resolutionMultiplier;
    glScalef(scale.x, scale.y, 1);
    glTranslatef(ScreenOrigin.x, ScreenOrigin.y, 0);
}

void mountain::Renderer::ResetModelViewMatrix()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const Vector2 scale = 1 / (Resolution / TargetResolution);
    glScalef(scale.x, scale.y, 1);
}

void mountain::Renderer::UpdateWindowFields()
{
    int windowX, windowY, windowW, windowH;
    glfwGetWindowPos(mWindow, &windowX, &windowY);
    glfwGetWindowSize(mWindow, &windowW, &windowH);
    WindowPosition = Vector2i(windowX, windowY);
    WindowSize = Vector2i(windowW, windowH);
}
