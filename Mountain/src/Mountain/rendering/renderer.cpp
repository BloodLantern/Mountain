#include "Mountain/rendering/renderer.hpp"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Mountain/screen.hpp"
#include "Mountain/window.hpp"
#include "Mountain/file/file_manager.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/utils/logger.hpp"

void Mountain::Renderer::PushRenderTarget(RenderTarget& renderTarget)
{
    renderTarget.Use();
    m_RenderTargets.push(&renderTarget);
}

Mountain::RenderTarget& Mountain::Renderer::PopRenderTarget()
{
    RenderTarget* renderTarget = m_RenderTargets.top();
    m_RenderTargets.pop();

    if (!m_RenderTargets.empty())
        m_RenderTargets.top()->Use();
    else
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return *renderTarget;
}

Mountain::OpenGlVersion& Mountain::Renderer::GetOpenGlVersion() { return m_GlVersion; }

bool Mountain::Renderer::Initialize(const std::string_view windowTitle, const Vector2i windowSize, const bool_t vsync, const OpenGlVersion &glVersion)
{
    Logger::LogDebug("Initializing renderer");

    m_GlVersion = glVersion;

    Window::Initialize(windowTitle, windowSize, vsync, glVersion);

    // Setup GLAD: load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))  // NOLINT(clang-diagnostic-cast-function-type-strict)
    {
        Logger::LogFatal("Failed to initialize GLAD");
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, windowSize.x, windowSize.y);

    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable program point size mode
    glEnable(GL_PROGRAM_POINT_SIZE);

    m_RenderTarget = new RenderTarget(windowSize, MagnificationFilter::Linear);

    ResourceManager::LoadAllBinaries();

    Draw::Initialize();

    // Setup FreeType
    if (FT_Init_FreeType(&m_Freetype))
    {
        Logger::LogError("Failed to initialize FreeType");
        Window::Shutdown();
        return false;
    }
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::StyleColorsDark();
    
    ImGui_ImplGlfw_InitForOpenGL(Window::GetHandle(), true);
    ImGui_ImplOpenGL3_Init(glVersion.glsl);

    io.Fonts->AddFontDefault();

    return true;
}

void Mountain::Renderer::PreFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
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

    Draw::RenderTarget(*m_RenderTarget);
    
    // End ImGui frame
    ImGui::Render();
    
    Vector2i framebufferSize;
    glfwGetFramebufferSize(Window::GetHandle(), &framebufferSize.x, &framebufferSize.y);
    glViewport(0, 0, framebufferSize.x, framebufferSize.y);
    
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
    Logger::LogDebug("Shutting down renderer");
    
    // Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyPlatformWindows();
	ImGui::DestroyContext();
    
    Draw::Shutdown();
    FT_Done_FreeType(m_Freetype);

    delete m_RenderTarget;
    
    Window::Shutdown();
}
