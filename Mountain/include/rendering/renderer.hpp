#pragma once

#include <GLFW/glfw3.h>

namespace mountain
{
    typedef void (*UserGameLoop)(double deltaTime);

    struct OpenGLVersion
    {
        const char* glslVersion;
        int major;
        int minor;
    };

    class Renderer
    {
    public:
        static Renderer* sInstance;

        Renderer();
        Renderer(OpenGLVersion glVersion);

        void Initialize(const int windowWidth = 1280, const int windowHeight = 720, const bool vsync = true);
        void MainLoop();
        void Shutdown();

        void BindUserGameLoop(UserGameLoop userGameLoop) { mUserGameLoop = userGameLoop; }
        void MakeOpenGLCoordinatesAbsolute(const int windowX, const int windowY, const int windowWidth, const int windowHeight);

        void SetPixelMode(const bool pixelMode) { mPixelMode = pixelMode; }
        OpenGLVersion GetOpenGLVersion() const { return mGlVersion; }

    private:
        bool mPixelMode = false;
        GLFWwindow* mWindow = nullptr;
        double mDeltaTime = 0.0;
        UserGameLoop mUserGameLoop = nullptr;
        OpenGLVersion mGlVersion;
    };
}
