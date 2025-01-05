#include "test_game.hpp"

#include <iostream>

#include <ImGui/imgui.h>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/screen.hpp"
#include "Mountain/file/file_manager.hpp"
#include "Mountain/input/input.hpp"
#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/rendering/graphics.hpp"
#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/scene/entity.hpp"
#include "Mountain/scene/component/audio_listener.hpp"
#include "Mountain/utils/imgui_utils.hpp"
#include "Mountain/utils/logger.hpp"

#include "spin_component.hpp"
#include "Mountain/rendering/effect.hpp"
#include "Mountain/utils/file_system_watcher.hpp"

using namespace Mountain;

GameExample::GameExample(const char_t* const windowTitle)
    : Game(windowTitle)
    , renderTarget(BaseResolution, Graphics::MagnificationFilter::Nearest)
    , debugRenderTarget(Window::GetSize(), Graphics::MagnificationFilter::Nearest)
{
    //renderTarget.ambientLight = Color(0.1f);
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

    Game::Initialize();
}

void GameExample::LoadResources()
{
    /*FileManager::LoadDirectory("assets");
    ResourceManager::LoadAll();*/

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

    /*Entity* entity = new Entity(static_cast<Vector2>(BaseResolution) * 0.5f);
    entities.Add(entity);
    entity->AddComponent<SpinComponent>();

    character = new AnimatedCharacter({ 30.f, 80.f });
    entities.Add(character);

    player->LoadResources();

    font = ResourceManager::LoadFont("assets/font.ttf", 30);*/

    vignette.effect.LoadResources();
    filmGrain.effect.LoadResources();
}

void GameExample::Shutdown()
{
    for (const Entity* const entity : entities)
        delete entity;

    delete player;

    Game::Shutdown();
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
    
    /*for (Entity* const entity : entities)
        entity->Render();

    const Vector2 resolutionFactor = renderTarget.GetSize() / BaseResolution;

    static constexpr std::array Points {
        Vector2{ 1.f, 0.f },
        Vector2{ static_cast<float_t>(BaseResolution.x), 0.f },
        Vector2{ static_cast<float_t>(BaseResolution.x), static_cast<float_t>(BaseResolution.y) - 1.f },
        Vector2{ 1.f, static_cast<float_t>(BaseResolution.y) - 1.f }
    };

    Draw::Line(Points[0], Points[1], Color::Red());
    Draw::Line(Points[1], Points[2], Color::Green());
    Draw::Line(Points[2], Points[3], Color::Blue());
    Draw::Line(Points[3], Points[0], Color::White());

    // Screen origin
    Draw::Line(Vector2::One() * -15.f, Vector2::One() * 15.f, Color::Red(), Color::Green());
    Draw::Line(Vector2(15.f, -15.f), Vector2(-15.f, 15.f), Color::Blue(), Color::White());

    static constexpr std::array TrianglePoints {
        Vector2(100.f, 40.f),
        Vector2(80.f, 80.f),
        Vector2(120.f, 90.f)
    };
    
    Draw::Triangle(TrianglePoints[0], TrianglePoints[1], TrianglePoints[2], Color::Aqua());
    
    Draw::TriangleFilled(TrianglePoints[0] * 2.f, TrianglePoints[1] * 2.f, TrianglePoints[2] * 2.f, Color::Brown());

    Draw::RectangleFilled(Vector2(23.f), Vector2(54.f, 34.f), Color::Azure());
    Draw::RectangleFilled(Vector2(27.f), Vector2(46.f, 26.f), Color::Cornsilk());

    Draw::Rectangle(Vector2(20.f), Vector2(60.f, 40.f), Color::Goldenrod());
    Draw::Rectangle(Vector2(25.f), Vector2(50.f, 30.f), Color::Lavender());

    Draw::CircleFilled(Vector2(130.f), 15.f * std::min(resolutionFactor.x, resolutionFactor.y), Color::Khaki());
    Draw::Circle(Vector2(130.f), 15.f * std::min(resolutionFactor.x, resolutionFactor.y), Color::Salmon());
    
    Draw::Circle(Vector2(100.f, 130.f), 35.f * std::min(resolutionFactor.x, resolutionFactor.y), Color::Salmon());
    
    Draw::TriangleFilled(Vector2(160.f, 70.f), Vector2(140.f, 110.f), Vector2(180.f, 110.f), Color::Red(), Color::Green(), Color::Blue());

    Pointer<Texture> oldLady = ResourceManager::Get<Texture>("assets/oldlady/idle00.png");
    Draw::Texture(*oldLady, { 10.f, 80.f });
    Draw::Texture(*oldLady, { 10.f, 90.f });
    Draw::Texture(*oldLady, { 10.f, 100.f });
    Draw::Texture(*oldLady, { 10.f, 110.f });
    Draw::Texture(*oldLady, { 10.f, 120.f });
    Draw::Texture(*oldLady, { 10.f, 130.f });
    Draw::Texture(*oldLady, { 10.f, 140.f });
    Draw::Texture(*oldLady, { 10.f, 150.f });
    Draw::Texture(*oldLady, { 10.f, 160.f });

    player->Render();*/

    particleSystem.Render();

    //Draw::Text(*font, "Hello, tiny World!", { 90.f, 30.f });

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

        /*for (Entity* const entity : entities)
            entity->RenderDebug();

        player->RenderDebug();*/

        particleSystem.RenderDebug();

        Renderer::PopRenderTarget();

        Draw::RenderTarget(debugRenderTarget);
    }

    /*Draw::Texture(*oldLady, { 10.f, 80.f });

    Draw::Text(*font, "Hello, big World!", { 10.f, 160.f });*/

    ImGui::Begin("Debug");
    
    if (ImGuiUtils::PushCollapsingHeader("Window"))
    {
        Vector2i position = Window::GetPosition();
        ImGui::DragInt2("Position", position.Data());
        Window::SetPosition(position);
        
        Vector2i size = Window::GetSize();
        ImGui::DragInt2("Size", size.Data());
        Window::SetSize(size);
        
        static bool_t fullscreen = false;
        ImGui::Checkbox("Enable fullscreen", &fullscreen);
        Window::SetFullscreen(fullscreen);

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
        ImGui::Text("Delta time: %.3f, Unscaled: %.3f, FPS: %.1f", Time::GetDeltaTime(), Time::GetDeltaTimeUnscaled(), 1.f / Time::GetDeltaTimeUnscaled());

        auto targetFps = Time::GetTargetFps();
        const uint16_t refreshRate = static_cast<uint16_t>(Screen::GetRefreshRate());
        constexpr uint16_t zero = 0;
        if (ImGuiUtils::Optional(
            &targetFps,
            refreshRate,
            refreshRate,
            [&](uint16_t& value) -> bool_t
            {
                return ImGui::DragScalar("Target FPS", ImGuiDataType_U16, &value, 1.f, &zero);
            }
        ))
        {
            Time::SetTargetFps(targetFps);
        }

        ImGui::Text("Frame time (without wait between frames): %.1fms", Time::GetLastFrameDuration() * 1000.f);
        ImGui::Text("Frame time left (if negative the game is lagging): %.1fms", (Time::GetTargetDeltaTime() - Time::GetLastFrameDuration()) * 1000.f);
        ImGui::Checkbox("Show inputs window", &showInputs);
        ImGui::SliderFloat("Time scale", &Time::timeScale, 0.f, 2.f);
        ImGui::Checkbox("Debug render", &debugRender);
        /*Sprite* s = character->GetComponent<Sprite>();
        float_t f = s->GetFrameDuration();
        const float_t oldF = f;
        ImGui::DragFloat("Old lady animation speed", &f, 0.01f);
        if (oldF != f)
            s->SetFrameDuration(f);*/

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
}
