#include "test_game.hpp"

#include <iostream>

#include <ImGui/imgui.h>

#include "collision/collide.hpp"
#include "input/input.hpp"
#include "rendering/draw.hpp"
#include "rendering/renderer.hpp"
#include "scene/entity.hpp"
#include "utils/logger.hpp"
#include "utils/random.hpp"

#include "screen.hpp"
#include "spin_component.hpp"
#include "audio/audio.hpp"
#include "audio/component/audio_listener.hpp"
#include "file/file_manager.hpp"
#include "input/time.hpp"
#include "magic_enum/magic_enum.hpp"
#include "resource/resource_manager.hpp"
#include "utils/imgui_utils.hpp"

using namespace Mountain;

GameExample::GameExample(const char_t* const windowTitle)
    : Game(windowTitle)
    , renderTarget(BaseResolution, MagnificationFilter::Nearest)
{
}

void GameExample::Initialize()
{
    ballCount = 0;

    player = new Player({ 10.f, 100.f });
}

void GameExample::LoadResources()
{
    FileManager::LoadDirectory("assets");
    ResourceManager::LoadAll();

    Entity* entity = new Entity(static_cast<Vector2>(BaseResolution) * 0.5f);
    entities.Add(entity);
    entity->AddComponent<SpinComponent>();

    player->LoadResources();

    font = ResourceManager::LoadFont("assets/font.ttf", 30);
}

void GameExample::Shutdown()
{
    for (const Entity* const entity : entities)
        delete entity;

    delete player;
}

void GameExample::Update()
{
    for (Entity* const entity : entities)
        entity->Update();

    player->Update();
}

bool_t showInputs = false;
bool_t debugRender = true;
int32_t circleSegments = 20;

void GameExample::Render()
{
    Draw::Clear(Color::CornflowerBlue());
    
    Renderer::PushRenderTarget(renderTarget);
    Draw::Clear(Color::Transparent());
    
    for (Entity* const entity : entities)
        entity->Render();

    const Vector2 resolutionFactor = renderTarget.GetSize() / BaseResolution;

    const std::array points {
        Vector2(1.f, 0.f) * resolutionFactor,
        Vector2(320.f, 0.f) * resolutionFactor,
        Vector2(320.f, 179.f) * resolutionFactor,
        Vector2(1.f, 179.f) * resolutionFactor
    };

    Draw::Line(points[0], points[1], Color::Red());
    Draw::Line(points[1], points[2], Color::Green());
    Draw::Line(points[2], points[3], Color::Blue());
    Draw::Line(points[3], points[0], Color::Black());

    // Screen origin
    Draw::Line(Vector2::One() * -15.f * resolutionFactor, Vector2::One() * 15.f * resolutionFactor, Color::Red());
    Draw::Line(Vector2(15.f, -15.f) * resolutionFactor, Vector2(-15.f, 15.f) * resolutionFactor, Color::Red());

    Draw::Points(points);

    constexpr std::array trianglePoints {
        Vector2(100.f, 40.f),
        Vector2(80.f, 80.f),
        Vector2(120.f, 90.f)
    };
    
    Draw::Triangle(trianglePoints[0] * resolutionFactor, trianglePoints[1] * resolutionFactor, trianglePoints[2] * resolutionFactor, Color::Aqua());
    
    Draw::TriangleFilled(trianglePoints[0] * resolutionFactor * 2.f, trianglePoints[1] * resolutionFactor * 2.f, trianglePoints[2] * resolutionFactor * 2.f, Color::Brown());

    Draw::Rectangle(Vector2(20.f) * resolutionFactor, Vector2(60.f, 40.f) * resolutionFactor, Color::Goldenrod());

    Draw::Circle(Vector2(130.f) * resolutionFactor, 15.f * std::min(resolutionFactor.x, resolutionFactor.y), Color::Salmon(), circleSegments);

    Draw::CircleDotted(Vector2(160.f, 130.f) * resolutionFactor, 15.f * std::min(resolutionFactor.x, resolutionFactor.y), Color::Firebrick(), circleSegments / 2);

    Draw::CircleFilled(Vector2(100.f, 130.f) * resolutionFactor, 15.f * std::min(resolutionFactor.x, resolutionFactor.y), Color::Khaki());
    
    Draw::TriangleFilled(Vector2(160.f, 70.f) * resolutionFactor, Vector2(140.f, 110.f) * resolutionFactor, Vector2(180.f, 110.f) * resolutionFactor, Color::Red(), Color::Green(), Color::Blue());

    Draw::Texture(*ResourceManager::Get<Texture>("assets/oldlady/idle00.png"), { 10.f, 80.f });

    player->Render();

    if (debugRender)
    {
        for (Entity* const entity : entities)
            entity->DebugRender();

        player->DebugRender();
    }

    Draw::Text(*font, "Hello, tiny World!", { 100.f, 30.f });

    Renderer::PopRenderTarget();

    Draw::RenderTarget(renderTarget, camera.position, Window::GetSize() / renderTarget.GetSize() * camera.scale, camera.rotation);

    Draw::Texture(*ResourceManager::Get<Texture>("assets/oldlady/idle00.png"), { 10.f, 80.f });

    Draw::Text(*font, "Hello, big World!", { 10.f, 160.f }, 2.f);

    ImGui::Begin("Debug");
    
    if (ImGui::CollapsingHeader("Window"))
    {
        Vector2i position = Window::GetPosition();
        ImGui::DragInt2("Position", position.Raw());
        Window::SetPosition(position);
        
        Vector2i size = Window::GetSize();
        ImGui::DragInt2("Size", size.Raw());
        Window::SetSize(size);
        
        if (ImGui::BeginCombo("Fullscreen mode", magic_enum::enum_name(Window::GetFullscreenMode()).data()))
        {
            for (size_t i = 0; i < FullscreenModeCount; ++i)
            {
                const FullscreenMode mode = static_cast<FullscreenMode>(i);
                if (ImGui::Selectable(magic_enum::enum_name(mode).data()))
                    Window::SetFullscreenMode(mode);
            }
            ImGui::EndCombo();
        }
    }
    
    if (ImGui::CollapsingHeader("Renderer"))
    {
        ImGui::PushID("Renderer");
        
        static Vector2i resolution = renderTarget.GetSize();
        ImGui::DragInt2("Game resolution", resolution.Raw());
        if (resolution != renderTarget.GetSize())
            renderTarget.SetSize(resolution);
        
        ImGui::SeparatorText("Camera");
        ImGui::DragFloat2("Position", camera.position.Raw());
        float_t cameraRotation = camera.rotation * Calc::Rad2Deg;
        ImGui::DragFloat("Rotation", &cameraRotation);
        camera.rotation = cameraRotation * Calc::Deg2Rad;
        ImGui::DragFloat("Scale", &camera.scale, 0.1f, 0.1f);

        camera.UpdateMatrix();
        
        ImGui::PopID();
    }
    
    if (ImGui::CollapsingHeader("Tests"))
    {
        ImGui::Text("Delta time: %.3f, Unscaled: %.3f, FPS: %.1f", Time::GetDeltaTime(), Time::GetDeltaTimeUnscaled(), 1.f / Time::GetDeltaTimeUnscaled());
        ImGui::Checkbox("Show inputs window", &showInputs);
        ImGui::SliderFloat("Time scale", &Time::timeScale, 0.f, 2.f);
        ImGui::Checkbox("Debug render", &debugRender);
        ImGui::DragInt("Circle segments", &circleSegments);
    }
    
    if (ImGui::CollapsingHeader("Player"))
    {
        ImGui::DragFloat2("Position", player->position.Raw());
        ImGui::DragFloat("Movement speed", &player->movementSpeed);
        
        AudioListener* listener = player->GetComponent<AudioListener>();
        float_t volume = listener->GetVolume();
        ImGui::SliderFloat("Audio volume", &volume, 0.f, 1.f);
        listener->SetVolume(volume);
    }
    
    ImGui::End();
 
    if (showInputs)
        ImGuiUtils::ShowInputsWindow();
}
