#include "TestGame.hpp"

#include <iostream>

#include <ImGui/imgui.h>

#include <Mountain/Globals.hpp>
#include <Mountain/Window.hpp>
#include <Mountain/Input/Time.hpp>
#include <Mountain/Rendering/Draw.hpp>

#include "Mountain/FileSystem/FileManager.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/ImGuiUtils.hpp"

#include "Scenes/ParticleSystemScene.hpp"

using namespace Mountain;

GameExample::GameExample(const char_t* const windowTitle)
    : Game(windowTitle, {1600, 900})
{
    m_Scenes.AddRange(
        new ParticleSystemScene
    );
}

/*template <Concepts::Effect T>
struct PostProcessingEffect
{
    bool_t enabled;
    T effect;
};

namespace
{
    PostProcessingEffect<Vignette> vignette;
    PostProcessingEffect<FilmGrain> filmGrain;

    template <Concepts::Effect T>
    void ShowEffect(
        const std::string& name,
        PostProcessingEffect<T>& effect,
        const std::type_identity_t<std::function<void(T& effect)>>& additionalAction = std::identity{}
    )
    {
        const static std::string CheckboxLabel = "##" + name + "Enabled";
        ImGui::Checkbox(CheckboxLabel.c_str(), &effect.enabled);
        ImGui::SameLine();
        if (ImGui::TreeNode(name.c_str()))
        {
            additionalAction(effect.effect);
            ImGui::TreePop();
        }
    }
}*/

void GameExample::LoadResources()
{
    // Each scene is responsible for loading and unloading resources
    m_Scenes.ForEach([](TestScene* scene) { scene->LoadPersistentResources(); });

    /*vignette.effect.LoadResources();
    filmGrain.effect.LoadResources();*/
}

void GameExample::Initialize()
{
    InitializeFileSystemWatchers();

    SetScene(m_Scenes.First());

    m_AssetsWatcher.Start();
    if (!NoBinaryResources)
        m_ShadersWatcher.Start();
}

void GameExample::Shutdown()
{
    m_AssetsWatcher.Stop();
    m_ShadersWatcher.Stop();

    m_Scenes.ForEach([](TestScene* scene) { scene->UnloadPersistentResources(); });
    m_Scenes.ForEach(OperationDelete<TestScene*>);
}

void GameExample::Update()
{
    m_ShadersToReloadMutex.lock();
    List<Pointer<ShaderBase>> reloadedShaders;
    for (auto shader : m_ShadersToReload)
    {
        if (reloadedShaders.Contains(shader))
            continue;

        Logger::LogInfo("Reloading shader resource {}", shader->GetName());

        shader->Reload();
        reloadedShaders.Add(shader);
    }
    m_ShadersToReload.Clear();
    m_ShadersToReloadMutex.unlock();

    if (m_ActiveScene)
    {
        m_ActiveScene->BeforeUpdate();
        m_ActiveScene->Update();
        m_ActiveScene->AfterUpdate();
    }
}

void GameExample::Render()
{
    Draw::Clear(m_ClearColor);

    if (m_ActiveScene)
    {
        m_ActiveScene->BeforeRender();
        m_ActiveScene->Render();
        m_ActiveScene->AfterRender();
    }

    /*vignette.effect.imageBindings.Emplace(Renderer::GetCurrentRenderTarget().GetTextureId(), 0u, Graphics::ImageShaderAccess::WriteOnly);
    filmGrain.effect.imageBindings.Emplace(Renderer::GetCurrentRenderTarget().GetTextureId(), 0u, Graphics::ImageShaderAccess::WriteOnly);
    if (vignette.enabled)
        vignette.effect.Apply(Renderer::GetCurrentRenderTarget().GetSize(), false);
    if (filmGrain.enabled)
        filmGrain.effect.Apply(Renderer::GetCurrentRenderTarget().GetSize(), false);
    vignette.effect.imageBindings.Clear();
    filmGrain.effect.imageBindings.Clear();*/

    if (m_EnableDebugRendering)
        RenderDebug();

    RenderImGui();
}

void GameExample::RenderDebug() const
{
    if (m_ActiveScene)
    {
        m_ActiveScene->BeforeRenderDebug();
        m_ActiveScene->RenderDebug();
        m_ActiveScene->AfterRenderDebug();
    }
}

void GameExample::RenderImGui()
{
    ImGui::Begin("Debug");

    ImGui::SeparatorText("Global settings");

    if (ImGuiUtils::PushCollapsingHeader("Window"))
    {
        Vector2i position = Window::GetPosition();
        ImGui::DragInt2("Position", position.Data());
        Window::SetPosition(position);

        Vector2i size = Window::GetSize();
        ImGui::DragInt2("Size", size.Data());
        Window::SetSize(size);

        static WindowMode windowMode = WindowMode::Windowed;
        ImGui::ComboEnum("Window mode", &windowMode);
        Window::SetWindowMode(windowMode);

        ImGuiUtils::PopCollapsingHeader();
    }

    if (ImGuiUtils::PushCollapsingHeader("Renderer"))
    {
        ImGui::ColorEdit4("Clear color", m_ClearColor.Data());

        /*ImGui::SeparatorText("Post processing effects");
        ShowEffect("Vignette", vignette, [](auto& e)
        {
            static float_t strength = 1.f;
            ImGui::DragFloat("strength", &strength, 0.01f, 0.f, 10.f);
            e.SetStrength(strength);
        });
        ShowEffect("Film Grain", filmGrain, [](auto& e)
        {
            static float_t intensity = 1.f;
            ImGui::DragFloat("intensity", &intensity, 0.01f, 0.f, 10.f);
            e.SetIntensity(intensity);
        });*/

        ImGuiUtils::PopCollapsingHeader();
    }

    static bool_t showDemoWindow = false;
    static bool_t showResourceManagerWindows = false;
    static bool_t showInputsWindow = false;
    static bool_t showPerformanceMonitoringWindow = false;

    if (ImGuiUtils::PushCollapsingHeader("Tests"))
    {
        ImGui::SliderFloat("Time scale", &Time::timeScale, 0.f, 2.f);
        ImGui::Checkbox("Debug render", &m_EnableDebugRendering);

        ImGui::Checkbox("Show inputs window", &showInputsWindow);
        ImGui::Checkbox("Show performance monitoring window", &showPerformanceMonitoringWindow);
        ImGui::Checkbox("Show ImGui demo window", &showDemoWindow);
        ImGui::Checkbox("Show File/Resource Manager windows", &showResourceManagerWindows);

        ImGuiUtils::PopCollapsingHeader();
    }

    ImGui::SeparatorText("Scene");

    const char_t* sceneComboPreview = "None";
    if (m_ActiveScene)
        sceneComboPreview = m_ActiveScene->GetName().c_str();

    if (ImGui::BeginCombo("Active scene", sceneComboPreview))
    {
        for (TestScene* scene : m_Scenes)
        {
            if (ImGui::Selectable(scene->GetName().c_str()))
                SetScene(scene);
        }
        ImGui::EndCombo();
    }

    if (m_ActiveScene)
    {
        m_ActiveScene->BeforeRenderImGui();
        if (m_ActiveScene->GetImGuiHeaderOpen())
            m_ActiveScene->RenderImGui();
        m_ActiveScene->AfterRenderImGui();
    }

    ImGui::End();

    if (showDemoWindow)
        ImGui::ShowDemoWindow();

    if (showResourceManagerWindows)
    {
        ImGuiUtils::ShowFileManager();
        ImGuiUtils::ShowResourceManager();
    }

    if (showInputsWindow)
        ImGuiUtils::ShowInputsWindow();

    if (showPerformanceMonitoringWindow)
        ImGuiUtils::ShowPerformanceMonitoring();
}

void GameExample::SetScene(TestScene* newScene)
{
    if (m_ActiveScene)
        m_ActiveScene->End();

    m_ActiveScene = newScene;

    if (m_ActiveScene)
        m_ActiveScene->Begin();
}

void GameExample::InitializeFileSystemWatchers()
{
    m_AssetsWatcher.recursive = true;
    m_AssetsWatcher.onCreated += [](const std::filesystem::path& path)
    {
        if (is_directory(path))
            return;

        FileManager::Load(path);
        ResourceManager::LoadAll();
    };
    m_AssetsWatcher.onModified += [](const std::filesystem::path& path)
    {
        if (is_directory(path))
            return;

        auto f = FileManager::Get<File>(path);
        if (!f)
            return;
        f->Reload();
        auto r = f->GetResource();
        if (r)
            r->Reload();
    };

    if (!NoBinaryResources)
    {
        // Setup shader hot reloading
        std::string builtinShadersPath = Utils::GetBuiltinShadersPath();
        if (builtinShadersPath.ends_with('/'))
            builtinShadersPath.pop_back();
        m_ShadersWatcher.SetPath(builtinShadersPath);
        m_ShadersWatcher.recursive = true;
        m_ShadersWatcher.onModified += [&](const std::filesystem::path& path)
        {
            m_ShadersToReloadMutex.lock();
            if (is_directory(path))
            {
                for (const auto& p : std::filesystem::recursive_directory_iterator{
                         FileManager::Get<Directory>(relative(path))->GetPath()
                     })
                {
                    if (p.is_directory())
                    {
                        continue;
                    }

                    ReloadShader(p);
                }
                m_ShadersToReloadMutex.unlock();
                return;
            }

            std::string pathString = path.generic_string();
            if (pathString.ends_with('~'))
                pathString.pop_back();

            ReloadShader(relative(std::filesystem::path{ pathString }));
            m_ShadersToReloadMutex.unlock();
        };
    }
}

void GameExample::ReloadShader(const std::filesystem::path& path)
{
    Logger::LogInfo("Reloading shader file {}", path);

    const std::string extension = path.extension().string();

    auto f = FileManager::Get(Utils::GetBuiltinShadersPath() + relative(path, Utils::GetBuiltinShadersPath()).generic_string());
    if (!f)
        return;
    f->Reload();

    for (auto& shaderBase : ResourceManager::FindAll<ShaderBase>())
    {
        if (shaderBase->dependentShaderFiles.contains(path))
            m_ShadersToReload.Add(shaderBase);
    }

    const bool_t isDrawShader = Utils::StringArrayContains(Shader::VertexFileExtensions, extension) ||
                                Utils::StringArrayContains(Shader::FragmentFileExtensions, extension);
    const std::string name = isDrawShader ? path.parent_path().generic_string() : path.generic_string();

    if (!ResourceManager::Contains(name))
        return;

    const Pointer s = ResourceManager::Get<ShaderBase>(name);

    m_ShadersToReload.Add(s);
}
