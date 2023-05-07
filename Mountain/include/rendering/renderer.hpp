#pragma once

#include <GLFW/glfw3.h>
#include <vector2i.hpp>
#include <matrix4x4.hpp>

#include "color.hpp"

namespace mountain
{
    struct OpenGLVersion
    {
        const char* glsl = "#version 130";
        int major = 3;
        int minor = 0;
    };

    class Renderer
    {
    public:
        static Vector2 ScreenOrigin;
        static Vector2i Resolution;
        static Vector2i TargetResolution;
        static Vector2i WindowPosition;
        static Vector2i WindowSize;
        static Colorf ClearColor; // Color used to fill the window before each frame.
        static Matrix4x4 Camera; // This is the TRS matrix that will be applied before rendering.

        static void Initialize(const char* const windowTitle,
            const int windowWidth, const int windowHeight,
            const bool vsync, const OpenGLVersion& glVersion = OpenGLVersion());
        static void PreFrame();
        static void PostFrame();
        static void Shutdown();

        static void MakeOpenGLCoordinatesAbsolute(const int windowWidth, const int windowHeight);
        static void UpdateModelViewMatrix();
        static void ResetModelViewMatrix();

        static GLFWwindow* GetWindow() { return mWindow; }
        static OpenGLVersion& GetOpenGLVersion() { return mGlVersion; }
        static void SetVSync(const bool vsync) { glfwSwapInterval(vsync); }

    private:
        static GLFWwindow* mWindow;
        static OpenGLVersion mGlVersion;

        static void UpdateWindowFields();
    };
}
