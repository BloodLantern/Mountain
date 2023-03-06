#pragma once

#include <GLFW/glfw3.h>

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
        static Renderer* sInstance;

        bool pixelMode = false;
        Color clearColor = Color(0x73, 0x8C, 0x99);

        Renderer();
        Renderer(OpenGLVersion glVersion);

        void Initialize(const int windowWidth = 1280, const int windowHeight = 720, const bool vsync = true);
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
    };
}
