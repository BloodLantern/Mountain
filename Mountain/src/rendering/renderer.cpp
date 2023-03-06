#include "renderer.hpp"

#include <iostream>
#include <cassert>

mountain::Renderer* mountain::Renderer::sInstance = nullptr;

mountain::Renderer::Renderer()
    : Renderer(OpenGLVersion())
{
}

mountain::Renderer::Renderer(OpenGLVersion glVersion)
    : mGlVersion(glVersion)
{
    if (sInstance == nullptr)
        sInstance = this;
    else
        assert(false && "Renderer is a singleton.");
}

void mountain::Renderer::Initialize(const int windowWidth, const int windowHeight, const bool vsync)
{
    // Setup GLFW
    glfwSetErrorCallback(
        [](int error, const char* description)
        {
            fprintf(stderr, "GLFW error %d: %s\n", error, description);
        }
    );

    if (!glfwInit())
        assert(false && "Failed to initialize GLFW.");

    // GL 3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mGlVersion.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mGlVersion.minor);

    // Create window with graphics context
    mWindow = glfwCreateWindow(windowWidth, windowHeight, "Celeste", NULL, NULL);
    if (mWindow == NULL)
        assert(false && "Failed to create GLFW window.");

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(vsync); // Enable vsync
}

void mountain::Renderer::PreFrame()
{
    glfwPollEvents();

    glClearColor(clearColor.r / 255.f, clearColor.g / 255.f, clearColor.b / 255.f, clearColor.a / 255.f);
    glClear(GL_COLOR_BUFFER_BIT);
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

void mountain::Renderer::MakeOpenGLCoordinatesAbsolute(const int windowX, const int windowY, const int windowWidth, const int windowHeight)
{
    glViewport(windowX, windowY, windowWidth, windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(windowX, windowX + windowWidth, windowY, windowY + windowHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
