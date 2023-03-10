#pragma once

#include <GLFW/glfw3.h>
#include <vector2i.hpp>

#include "color.hpp"

namespace mountain
{
    struct OpenGLVersion
    {
        const char* const glsl = "#version 130";
        int major = 3;
        int minor = 0;
    };

    class Renderer
    {
    public:
        static Renderer* sInstance;

        Vector2i Resolution = Vector2i(1920, 1080);
        Vector2i WindowPosition;
        Vector2i WindowSize;
        Colorf ClearColor = Colorf(0.45f, 0.55f, 0.60f);

        Renderer();
        Renderer(OpenGLVersion glVersion);

        void Initialize(const char* const windowTitle, const int windowWidth = 1280, const int windowHeight = 720, const bool vsync = true);
        void PreFrame();
        void PostFrame();
        void Shutdown();

        void MakeOpenGLCoordinatesAbsolute(const int windowX, const int windowY, const int windowWidth, const int windowHeight);

        GLFWwindow* GetWindow() { return mWindow; }
        OpenGLVersion GetOpenGLVersion() const { return mGlVersion; }
        OpenGLVersion& GetOpenGLVersion() { return mGlVersion; }

    private:
        GLFWwindow* mWindow = nullptr;
        OpenGLVersion mGlVersion;

        void UpdateWindowFields();
    };
}
