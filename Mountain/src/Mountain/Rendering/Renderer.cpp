#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Rendering/Renderer.hpp"

#include <glad/glad.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_sdl3.h>

#include <ft2build.h>

#include "Mountain/Globals.hpp"

#include FT_FREETYPE_H

#include "Mountain/Screen.hpp"
#include "Mountain/Window.hpp"
#include "Mountain/FileSystem/FileManager.hpp"
#include "Mountain/Rendering/Draw.hpp"
#include "Mountain/Rendering/ParticleSystem.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/Logger.hpp"

namespace
{
    void OpenGlDebugCallback(const GLenum source, const GLenum type, GLuint, const GLenum severity, const GLsizei length, const GLchar* message, const void*)
    {
        Mountain::Logger::LogLevel level;
        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                level = Mountain::Logger::LogLevel::Error;
                break;

            case GL_DEBUG_SEVERITY_MEDIUM:
                level = Mountain::Logger::LogLevel::Warning;
                break;

            case GL_DEBUG_SEVERITY_LOW:
                level = Mountain::Logger::LogLevel::Info;
                break;

            case GL_DEBUG_SEVERITY_NOTIFICATION:
                return; // No need to log notifications

            default:
                level = Mountain::Logger::LogLevel::Info;
        }

        std::string_view src;
        switch (source) {
            case GL_DEBUG_SOURCE_API:
                src = "API";
                break;

            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                src = "Window system";
                break;

            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                src = "Shader compiler";
                break;

            case GL_DEBUG_SOURCE_THIRD_PARTY:
                src = "Third party";
                break;

            case GL_DEBUG_SOURCE_APPLICATION:
                src = "Application";
                break;

            case GL_DEBUG_SOURCE_OTHER:
                src = "Other";
                break;

            default:
                src = "Unknown";
        }

        std::string_view t;
        switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                t = "Error";
                break;

            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                t = "Deprecated behavior";
                break;

            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                t = "Undefined behavior";
                break;

            case GL_DEBUG_TYPE_PORTABILITY:
                t = "Portability";
                break;

            case GL_DEBUG_TYPE_PERFORMANCE:
                t = "Performance";
                break;

            case GL_DEBUG_TYPE_OTHER:
                t = "Other";
                break;

            case GL_DEBUG_TYPE_MARKER:
                t = "Marker";
                break;

            default:
                t = "Unknown";
        }

        if (Mountain::BreakOnGraphicsError && level == Mountain::Logger::LogLevel::Error)
            __debugbreak();

        Mountain::Logger::Log(level, "[OpenGL] Log of type {} received from {}: {}", t, src, std::string_view(message, length));
    }
}

void Mountain::Renderer::PushRenderTarget(RenderTarget& renderTarget)
{
    Draw::Flush();

    renderTarget.Use();
    m_RenderTargets.push(&renderTarget);
}

Mountain::RenderTarget& Mountain::Renderer::PopRenderTarget()
{
    Draw::Flush();

    RenderTarget* renderTarget = m_RenderTargets.top();
    m_RenderTargets.pop();

    if (!m_RenderTargets.empty())
        m_RenderTargets.top()->Use();
    else
        BindFramebuffer(Graphics::FramebufferType::Framebuffer, 0);

    return *renderTarget;
}

Mountain::RenderTarget& Mountain::Renderer::GetCurrentRenderTarget()
{
    if (m_RenderTargets.empty())
        THROW(InvalidOperationException{"Cannot get the current RenderTarget outside of the Game::Render() function"});

    return *m_RenderTargets.top();
}

Mountain::RenderTarget& Mountain::Renderer::GetDefaultRenderTarget() { return *m_RenderTarget; }

void Mountain::Renderer::DebugString(std::string str, const float_t duration, const Color& color)
{
    m_DebugStrings.Insert(
        0,
        {
            .str = std::move(str),
            .time = DateTime::Now(),
            .color = color,
            .duration = duration
        }
    );
}

void Mountain::Renderer::DebugString(DebugStringData data)
{
    m_DebugStrings.Insert(0, std::move(data));
}

Mountain::OpenGlVersion& Mountain::Renderer::GetOpenGlVersion() { return m_GlVersion; }

bool_t Mountain::Renderer::Initialize(const std::string& windowTitle, const Vector2i windowSize, const OpenGlVersion& glVersion)
{
    Logger::LogVerbose("Initializing renderer");

    m_GlVersion = glVersion;

    Window::Initialize(windowTitle, windowSize, glVersion);

    // Setup GLAD: load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)))  // NOLINT(clang-diagnostic-cast-function-type-strict)
        THROW(Exception{"Failed to initialize GLAD"});

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback(OpenGlDebugCallback, nullptr);
#else
    if (BreakOnGraphicsError)
        Logger::LogWarning("Mountain::BreakOnGraphicsError has been set when not in a debug build, this won't do anything!");
#endif

    Graphics::SetViewport(0, 0, windowSize.x, windowSize.y);

    // Enable transparency
    EnableConstant(Graphics::Constant::Blend);
    EnableConstant(Graphics::Constant::ProgramPointSize);
    SetBlendFunction(Graphics::BlendFunction::SrcAlpha, Graphics::BlendFunction::OneMinusSrcAlpha);

    m_RenderTarget = new RenderTarget(windowSize, Graphics::MagnificationFilter::Linear);
    m_RenderTarget->SetDebugName("Viewport RenderTarget");

    Draw::Initialize();

    // Setup FreeType
    if (FT_Init_FreeType(&m_Freetype))
    {
        Logger::LogError("Failed to initialize FreeType");
        return false;
    }

    if (NoBinaryResources)
    {
        if (BuiltinShadersPath.empty() || BuiltinAssetsPath.empty())
            THROW(InvalidGlobalValueException{"NoBinaryResources is true but at least one of BuiltinShadersPath and BuiltinAssetsPath hasn't been specified"});

        FileManager::LoadDirectory(BuiltinShadersPath);
        FileManager::LoadDirectory(BuiltinAssetsPath);
        ResourceManager::LoadAll();
    }
    else
    {
        ResourceManager::LoadAllBinaries();
    }

    Draw::LoadResources();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(Window::GetHandle(), Window::GetContext());
    ImGui_ImplOpenGL3_Init(glVersion.glsl);

    io.Fonts->AddFontDefault();
    m_DefaultFont = ResourceManager::GetFont(Utils::GetBuiltinAssetsPath() + "font.ttf", 12);

    return true;
}

void Mountain::Renderer::PreFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    Window::UpdateFields();

    const Vector2i windowSize = Window::GetSize();
    if (windowSize != m_RenderTarget->GetSize())
        m_RenderTarget->SetSize(windowSize);

    PushRenderTarget(*m_RenderTarget);
}

void Mountain::Renderer::PostFrame()
{
    PopRenderTarget();

    if (!m_RenderTargets.empty())
        THROW(InvalidOperationException{"RenderTarget push/pop mismatch, e.g. a RenderTarget that was pushed hasn't been popped"});

    Draw::RenderTarget(*m_RenderTarget);

    // Draw debug strings
    const DateTime now = DateTime::Now();
    for (size_t i = 0; i < m_DebugStrings.GetSize(); i++)
    {
        const DebugStringData& data = m_DebugStrings[i];
        if ((now - data.time).GetTotalSeconds() > data.duration)
        {
            m_DebugStrings.RemoveAt(i--);
            continue;
        }

        Draw::Text(*m_DefaultFont, data.str, Vector2{20.f, 20.f + static_cast<float_t>(i) * 20.f}, 1.f, data.color);
    }

    if (m_DebugStrings.GetSize() > 2 && m_DebugStrings.GetSize() * 2 < m_DebugStrings.GetCapacity())
        m_DebugStrings.Shrink();

    Draw::Flush();

    // End ImGui frame
    ImGui::Render();

    const Vector2i framebufferSize = Window::GetFramebufferSize();
    Graphics::SetViewport(0, 0, framebufferSize.x, framebufferSize.y);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        Window::MakeContextCurrent();
    }
}

void Mountain::Renderer::Shutdown()
{
    Logger::LogVerbose("Shutting down renderer");

    // Cleanup
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyPlatformWindows();
	ImGui::DestroyContext();

    Draw::Shutdown();
    FT_Done_FreeType(m_Freetype);

    delete m_RenderTarget;

    Window::Shutdown();
}
