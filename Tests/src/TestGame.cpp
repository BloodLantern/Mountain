#include "Common.hpp"

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

#include "Scenes/AudioScene.hpp"
#include "Scenes/ParticleSystemScene.hpp"
#include "Scenes/PostProcessingEffectsScene.hpp"
#include "Scenes/SpriteAnimationsScene.hpp"

using namespace Mountain;

TestGame::TestGame(const char_t* const windowTitle)
    : Game(windowTitle, {1600, 900})
{
    m_Scenes.AddRange(
        new ParticleSystemScene,
        new PostProcessingEffectsScene,
        new SpriteAnimationsScene,
        new AudioScene
    );

    // Sort the scenes alphabetically
    m_Scenes.Sort([](const TestScene* lhs, const TestScene* rhs) { return lhs->GetName() < rhs->GetName(); });
}

void TestGame::LoadResources()
{
    // Each scene is responsible for loading and unloading resources
    m_Scenes.ForEach([](TestScene* scene) { scene->LoadPersistentResources(); });
}

void TestGame::Initialize()
{
    InitializeFileSystemWatchers();

    m_AssetsWatcher.Start();
    if (NoBinaryResources)
        m_ShadersWatcher.Start();
}

void TestGame::Shutdown()
{
    m_AssetsWatcher.Stop();
    m_ShadersWatcher.Stop();

    m_Scenes.ForEach([](TestScene* scene) { scene->UnloadPersistentResources(); });
    m_Scenes.ForEach(OperationDelete<TestScene*>);
}

void TestGame::Update()
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

    HandleSceneChange();

    if (m_ActiveScene)
    {
        m_ActiveScene->BeforeUpdate();
        m_ActiveScene->Update();
        m_ActiveScene->AfterUpdate();
    }
}

void TestGame::Render()
{
    Draw::Clear(m_ClearColor);

    if (m_ActiveScene)
    {
        m_ActiveScene->BeforeRender();
        m_ActiveScene->Render();
        m_ActiveScene->AfterRender();
    }

    if (m_EnableDebugRendering)
        RenderDebug();

    RenderImGui();
}

void TestGame::RenderDebug() const
{
    if (m_ActiveScene)
    {
        m_ActiveScene->BeforeRenderDebug();
        m_ActiveScene->RenderDebug();
        m_ActiveScene->AfterRenderDebug();
    }
}

void TestGame::RenderImGui()
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

    if (ImGuiUtils::PushCollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen))
    {
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
            m_ActiveScene->RenderImGui();
            m_ActiveScene->AfterRenderImGui();
        }

        ImGuiUtils::PopCollapsingHeader();
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

void TestGame::SetScene(TestScene* newScene)
{
    m_NextActiveScene = newScene;
}

void TestGame::InitializeFileSystemWatchers()
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

    if (NoBinaryResources)
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

void TestGame::ReloadShader(const std::filesystem::path& path)
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

    const bool_t isDrawShader = Utils::StringEnumerableContains(Shader::VertexFileExtensions, extension) ||
                                Utils::StringEnumerableContains(Shader::FragmentFileExtensions, extension);
    const std::string name = isDrawShader ? path.parent_path().generic_string() : path.generic_string();

    if (!ResourceManager::Contains(name))
        return;

    const Pointer s = ResourceManager::Get<ShaderBase>(name);

    m_ShadersToReload.Add(s);
}

void TestGame::HandleSceneChange()
{
    if (!m_NextActiveScene)
        return;

    if (m_ActiveScene)
    {
        m_ActiveScene->End();
        m_ActiveScene->UnloadResources();
    }

    m_ActiveScene = m_NextActiveScene;
    m_ActiveScene->LoadResources();
    m_ActiveScene->Begin();

    m_NextActiveScene = nullptr;
}
