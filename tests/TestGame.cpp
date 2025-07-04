#include "TestGame.hpp"

#include <iostream>

#include <ImGui/imgui.h>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Screen.hpp"
#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Ecs/Component/AudioListener.hpp"
#include "Mountain/FileSystem/FileManager.hpp"
#include "Mountain/Input/Input.hpp"
#include "Mountain/Input/Time.hpp"
#include "Mountain/Rendering/Draw.hpp"
#include "Mountain/Rendering/Effect.hpp"
#include "Mountain/Rendering/Graphics.hpp"
#include "Mountain/Rendering/Renderer.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/FileSystemWatcher.hpp"
#include "Mountain/Utils/ImGuiUtils.hpp"
#include "Mountain/Utils/Logger.hpp"
#include "Mountain/Utils/Random.hpp"

using namespace Mountain;

GameExample::GameExample(const char_t* const windowTitle)
    : Game(windowTitle)
    , renderTarget(BaseResolution, Graphics::MagnificationFilter::Nearest)
    , debugRenderTarget(Window::GetSize(), Graphics::MagnificationFilter::Nearest)
{
}

template <Concepts::EffectT T>
struct PostProcessingEffect
{
    bool_t enabled;
    T effect;
};

namespace
{
    FileSystemWatcher assetsWatcher{ "assets" };
    FileSystemWatcher shadersWatcher;
    List<Pointer<ShaderBase>> shadersToReload;
    std::mutex shadersToReloadMutex;

    bool_t showInputs = false;
    bool_t showPerformanceMonitoring = false;
    bool_t debugRender = true;

    PostProcessingEffect<Vignette> vignette;
    PostProcessingEffect<FilmGrain> filmGrain;

    template <Concepts::EffectT T>
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

    void ReloadShader(const std::filesystem::path& path)
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
                shadersToReload.Add(shaderBase);
        }

        const bool_t isDrawShader = Utils::StringArrayContains(Shader::VertexFileExtensions, extension) ||
                                    Utils::StringArrayContains(Shader::FragmentFileExtensions, extension);
        const std::string name = isDrawShader ? path.parent_path().generic_string() : path.generic_string();

        if (!ResourceManager::Contains(name))
            return;

        const Pointer s = ResourceManager::Get<ShaderBase>(name);

        shadersToReload.Add(s);
    }
}

void GameExample::LoadResources()
{
    assetsWatcher.recursive = true;
    assetsWatcher.onCreated += [](const std::filesystem::path& path)
    {
        if (is_directory(path))
            return;

        FileManager::Load(path);
        ResourceManager::LoadAll();
    };
    assetsWatcher.onModified += [](const std::filesystem::path& path)
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

    vignette.effect.LoadResources();
    filmGrain.effect.LoadResources();
}

void GameExample::Initialize()
{
    std::string builtinShadersPath = Utils::GetBuiltinShadersPath();
    if (builtinShadersPath.ends_with('/'))
        builtinShadersPath.pop_back();
    shadersWatcher.SetPath(builtinShadersPath);
    shadersWatcher.recursive = true;
    shadersWatcher.Start();
    shadersWatcher.onModified += [&](const std::filesystem::path& path)
    {
        shadersToReloadMutex.lock();
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
            shadersToReloadMutex.unlock();
            return;
        }

        std::string pathString = path.generic_string();
        if (pathString.ends_with('~'))
            pathString.pop_back();

        ReloadShader(relative(std::filesystem::path{ pathString }));
        shadersToReloadMutex.unlock();
    };

    player = new Player({ 10.f, 100.f }, renderTarget.NewLightSource());

    renderTarget.SetDebugName("Game RenderTarget");
    debugRenderTarget.SetDebugName("Game Debug RenderTarget");

    particleSystem.position = BaseResolution * 0.5f;//{ 250.f, 100.f };
    particleSystem.modules.AddRange(
        {
            std::make_shared<ParticleSystemModules::ColorOverLifetime>(),
            std::make_shared<ParticleSystemModules::ForceOverLifetime>(),
        }
    );
}

void GameExample::Shutdown()
{
    for (const Entity* const entity : entities)
        delete entity;

    delete player;
}

void GameExample::Update()
{
    shadersToReloadMutex.lock();
    List<Pointer<ShaderBase>> reloadedShaders;
    for (auto shader : shadersToReload)
    {
        if (reloadedShaders.Contains(shader))
            continue;

        Logger::LogInfo("Reloading shader resource {}", shader->GetName());

        shader->Reload();
        reloadedShaders.Add(shader);
    }
    shadersToReload.Clear();
    shadersToReloadMutex.unlock();

    for (Entity* const entity : entities)
        entity->Update();

    player->Update();

    particleSystem.Update();
}

void GameExample::Render()
{
    Draw::Clear(Color::Black());

    renderTarget.SetCameraMatrix(camera.matrix);
    Renderer::PushRenderTarget(renderTarget);
    static Color clearColor = Color::Black();
    Draw::Clear(clearColor);

    particleSystem.Render();

    Renderer::PopRenderTarget();

    Draw::RenderTarget(renderTarget, Vector2::Zero(), Window::GetSize() / renderTarget.GetSize());

    vignette.effect.imageBindings.Emplace(Renderer::GetCurrentRenderTarget().GetTextureId(), 0, Graphics::ImageShaderAccess::WriteOnly);
    filmGrain.effect.imageBindings.Emplace(Renderer::GetCurrentRenderTarget().GetTextureId(), 0, Graphics::ImageShaderAccess::WriteOnly);
    if (vignette.enabled)
        vignette.effect.Apply(Renderer::GetCurrentRenderTarget().GetSize(), false);
    if (filmGrain.enabled)
        filmGrain.effect.Apply(Renderer::GetCurrentRenderTarget().GetSize(), false);
    vignette.effect.imageBindings.Clear();
    filmGrain.effect.imageBindings.Clear();

    if (debugRender)
    {
        debugRenderTarget.SetCameraMatrix(camera.matrix);
        Renderer::PushRenderTarget(debugRenderTarget);
        Draw::Clear(Color::Transparent());

        particleSystem.RenderDebug();

        Renderer::PopRenderTarget();

        Draw::RenderTarget(debugRenderTarget);
    }

    ImGui::Begin("Debug");

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
        static Vector2i resolution = renderTarget.GetSize();
        ImGui::DragInt2("Game resolution", resolution.Data());
        if (resolution != renderTarget.GetSize())
            renderTarget.SetSize(resolution);
        ImGui::ColorEdit4("Clear color", clearColor.Data());

        ImGui::SeparatorText("Camera");
        if (ImGui::Button("Reset"))
        {
            camera.position = Vector2::Zero();
            camera.rotation = 0.f;
            camera.scale = Vector2::One();
        }
        ImGui::DragFloat2("Position", camera.position.Data());
        ImGui::DragAngle("Rotation", &camera.rotation);
        ImGui::DragFloat2("Scale", camera.scale.Data(), 0.01f, 0.1f);

        camera.UpdateMatrix();

        ImGui::SeparatorText("Lighting");
        ImGui::ColorEdit4("Ambient color", renderTarget.ambientLight.Data());
        LightSource& lightSource = *player->light;
        ImGui::ColorEdit4("Source color", lightSource.color.Data());
        ImGui::DragFloat("Source intensity", &lightSource.intensity, 0.1f);
        ImGui::DragFloat("Source radius", &lightSource.radius, 0.1f);
        ImGui::DragAngle("Source angle min", &lightSource.angleMin);
        ImGui::DragAngle("Source angle max", &lightSource.angleMax);
        ImGui::Text("Source position: %.2f, %.2f", lightSource.position.x, lightSource.position.y);

        ImGui::SeparatorText("Post processing effects");
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
        });

        ImGuiUtils::PopCollapsingHeader();
    }

    static bool_t showDemoWindow = false;
    static bool_t showResourceManagerWindows = false;
    if (ImGuiUtils::PushCollapsingHeader("Tests"))
    {
        ImGui::Checkbox("Show inputs window", &showInputs);
        ImGui::Checkbox("Show performance monitoring window", &showPerformanceMonitoring);
        ImGui::SliderFloat("Time scale", &Time::timeScale, 0.f, 2.f);
        ImGui::Checkbox("Debug render", &debugRender);

        ImGui::Checkbox("Show ImGui demo window", &showDemoWindow);

        ImGui::Checkbox("Show File/Resource Manager windows", &showResourceManagerWindows);

        ImGuiUtils::PopCollapsingHeader();
    }

    if (showDemoWindow)
        ImGui::ShowDemoWindow();
    if (showResourceManagerWindows)
    {
        ImGuiUtils::ShowFileManager();
        ImGuiUtils::ShowResourceManager();
    }

    if (ImGuiUtils::PushCollapsingHeader("Player"))
    {
        ImGui::DragFloat2("Position", player->position.Data());
        ImGui::DragFloat("Movement speed", &player->movementSpeed);

        AudioListener* listener = player->GetComponent<AudioListener>();
        float_t volume = listener->GetVolume();
        ImGui::SliderFloat("Audio volume", &volume, 0.f, 1.f);
        listener->SetVolume(volume);

        ImGuiUtils::PopCollapsingHeader();
    }

    if (ImGuiUtils::PushCollapsingHeader("Particle system"))
    {
        particleSystem.RenderImGui();

        ImGuiUtils::PopCollapsingHeader();
    }

    ImGui::End();

    if (showInputs)
        ImGuiUtils::ShowInputsWindow();

    if (showPerformanceMonitoring)
        ImGuiUtils::ShowPerformanceMonitoring();
}
