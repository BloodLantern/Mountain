#include "test_game.hpp"

#include <iostream>

#include <ImGui/imgui.h>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/screen.hpp"
#include "Mountain/file/file_manager.hpp"
#include "Mountain/input/input.hpp"
#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/scene/entity.hpp"
#include "Mountain/scene/component/audio_listener.hpp"
#include "Mountain/utils/imgui_utils.hpp"
#include "Mountain/utils/logger.hpp"

#include "spin_component.hpp"

using namespace Mountain;

GameExample::GameExample(const char_t* const windowTitle)
    : Game(windowTitle)
    , renderTarget(BaseResolution, MagnificationFilter::Nearest)
{
    renderTarget.ambientLight = Color(0.1f);
}

void GameExample::Initialize()
{
    ballCount = 0;

    player = new Player({ 10.f, 100.f });
    renderTarget.AddLightSource(player->GetComponent<LightSource>());

    particleSystem.position = { 250.f, 100.f };

    Game::Initialize();
}

void GameExample::LoadResources()
{
    FileManager::LoadDirectory("assets");
    ResourceManager::LoadAll();

    Entity* entity = new Entity(static_cast<Vector2>(BaseResolution) * 0.5f);
    entities.Add(entity);
    entity->AddComponent<SpinComponent>();

    character = new AnimatedCharacter({ 30.f, 80.f });
    entities.Add(character);

    player->LoadResources();

    font = ResourceManager::LoadFont("assets/font.ttf", 30);
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
    for (Entity* const entity : entities)
        entity->Update();

    player->Update();

    particleSystem.Update();
}

namespace
{
    bool_t showInputs = false;
    bool_t debugRender = true;
}

void GameExample::Render()
{
    Draw::Clear(Color::Transparent());

    renderTarget.SetCameraMatrix(camera.matrix);
    Renderer::PushRenderTarget(renderTarget);
    Draw::Clear(Color::Black());
    
    for (Entity* const entity : entities)
        entity->Render();

    const Vector2 resolutionFactor = renderTarget.GetSize() / BaseResolution;

    static constexpr std::array Points {
        Vector2(1.f, 0.f),
        Vector2(320.f, 0.f),
        Vector2(320.f, 179.f),
        Vector2(1.f, 179.f)
    };

    Draw::Line(Points[0], Points[1], Color::Red());
    Draw::Line(Points[1], Points[2], Color::Green());
    Draw::Line(Points[2], Points[3], Color::Blue());
    Draw::Line(Points[3], Points[0], Color::White());

    // Screen origin
    Draw::Line(Vector2::One() * -15.f, Vector2::One() * 15.f, Color::Red(), Color::Green());
    Draw::Line(Vector2(15.f, -15.f), Vector2(-15.f, 15.f), Color::Blue(), Color::White());

    //Draw::Points(Points);

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

    player->Render();

    particleSystem.Render();

    if (debugRender)
    {
        for (Entity* const entity : entities)
            entity->RenderDebug();

        player->RenderDebug();
    }

    Draw::Text(*font, "Hello, tiny World!", { 90.f, 30.f });

    Renderer::PopRenderTarget();

    Draw::RenderTarget(renderTarget, Vector2::Zero(), Window::GetSize() / renderTarget.GetSize());

    Draw::Texture(*oldLady, { 10.f, 80.f });

    Draw::Text(*font, "Hello, big World!", { 10.f, 160.f });

    ImGui::Begin("Debug");
    
    if (ImGui::CollapsingHeader("Window"))
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
    }
    
    if (ImGui::CollapsingHeader("Renderer"))
    {
        ImGui::PushID("Renderer");
        
        static Vector2i resolution = renderTarget.GetSize();
        ImGui::DragInt2("Game resolution", resolution.Data());
        if (resolution != renderTarget.GetSize())
            renderTarget.SetSize(resolution);
        
        ImGui::SeparatorText("Camera");
        if (ImGui::Button("Reset"))
        {
            camera.position = Vector2::Zero();
            camera.rotation = 0.f;
            camera.scale = Vector2::One();
        }
        ImGui::DragFloat2("Position", camera.position.Data());
        ImGui::DragAngle("Rotation", &camera.rotation);
        ImGui::DragFloat2("Scale", camera.scale.Data(), 0.1f, 0.1f);

        camera.UpdateMatrix();

        ImGui::SeparatorText("Lighting");
        ImGui::ColorEdit4("Ambient color", renderTarget.ambientLight.Data());
        LightSource* lightSource = player->GetComponent<LightSource>();
        ImGui::ColorEdit4("Source color", lightSource->color.Data());
        ImGui::DragFloat("Source intensity", &lightSource->intensity, 0.1f);
        ImGui::DragFloat("Source radius", &lightSource->radius, 0.1f);
        ImGui::DragAngle("Source angle min", &lightSource->angleMin, 0.1f);
        ImGui::DragAngle("Source angle max", &lightSource->angleMax, 0.1f);
        ImGui::Text("Source position: %.2f, %.2f", lightSource->GetPosition().x, lightSource->GetPosition().y);
        
        ImGui::PopID();
    }
    
    if (ImGui::CollapsingHeader("Tests"))
    {
        ImGui::Text("Delta time: %.3f, Unscaled: %.3f, FPS: %.1f", Time::GetDeltaTime(), Time::GetDeltaTimeUnscaled(), 1.f / Time::GetDeltaTimeUnscaled());
        ImGui::Checkbox("Show inputs window", &showInputs);
        ImGui::SliderFloat("Time scale", &Time::timeScale, 0.f, 2.f);
        ImGui::Checkbox("Debug render", &debugRender);
        Sprite* s = character->GetComponent<Sprite>();
        float_t f = s->GetFrameDuration();
        const float_t oldF = f;
        ImGui::DragFloat("Old lady animation speed", &f, 0.01f);
        if (oldF != f)
            s->SetFrameDuration(f);
    }
    
    if (ImGui::CollapsingHeader("Player"))
    {
        ImGui::DragFloat2("Position", player->position.Data());
        ImGui::DragFloat("Movement speed", &player->movementSpeed);
        
        AudioListener* listener = player->GetComponent<AudioListener>();
        float_t volume = listener->GetVolume();
        ImGui::SliderFloat("Audio volume", &volume, 0.f, 1.f);
        listener->SetVolume(volume);
    }

    if (ImGui::CollapsingHeader("Particle system"))
    {
        particleSystem.RenderImGui();
    }
    
    ImGui::End();
 
    if (showInputs)
        ImGuiUtils::ShowInputsWindow();
}
