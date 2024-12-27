#include "game_of_life.hpp"

#include "ImGui/imgui.h"
#include "Mountain/input/input.hpp"
#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/rendering/renderer.hpp"

namespace
{
    bool_t clickValue = false;
}

GameOfLife::GameOfLife(const char_t* title)
    : Game(title)
    , m_RenderTarget(Mountain::Window::GetSize(), Mountain::Graphics::MagnificationFilter::Nearest)
{
    m_Grid.SetSize(10, 10);
}

void GameOfLife::Initialize()
{
    Mountain::Window::onSizeChanged += [&](const Vector2i newSize) { m_RenderTarget.SetSize(newSize); };

    m_Grid.PreRenderGrid();

    Game::Initialize();
}

void GameOfLife::Update()
{
    if (!ImGui::GetIO().WantCaptureMouse)
    {
        m_Camera.HandleInputs();

        if (Mountain::Input::GetMouseButton(Mountain::MouseButton::Left))
        {
            const Vector2 pos = m_Camera.ToWorld(Mountain::Input::GetMousePosition());
            const uint64_t x = static_cast<uint64_t>(pos.x), y = static_cast<uint64_t>(pos.y);
            const uint64_t blockX = x / BlockSize, blockY = y / BlockSize;
            const uint8_t cellX = x % BlockSize, cellY = y % BlockSize;

            if (Mountain::Input::GetMouseButton(Mountain::MouseButton::Left, Mountain::MouseButtonStatus::Pressed))
                clickValue = !m_Grid.GetCell(blockX, blockY, cellX, cellY);

            m_Grid.SetCell(blockX, blockY, cellX, cellY, clickValue);
        }
    }

    if (Mountain::Input::GetKey(Mountain::Key::Escape))
        Mountain::Window::SetShouldClose(true);

    m_Camera.UpdateMatrices();

    if (m_ManualUpdate || (m_AutoUpdate && Calc::OnInterval(Mountain::Time::GetTotalTime(), Mountain::Time::GetLastTotalTime(), m_UpdateInterval)))
    {
        m_Grid.Update();
        m_ManualUpdate = false;
    }
}

void GameOfLife::Render()
{
    Mountain::Draw::Clear(Mountain::Color::Black());

    m_RenderTarget.SetCameraMatrix(m_Camera.GetMatrix());
    Mountain::Renderer::PushRenderTarget(m_RenderTarget);
    Mountain::Draw::Clear(Mountain::Color::Black());

    m_Grid.Render();
    Mountain::Draw::Rectangle(
        Vector2::Zero(),
        { static_cast<float_t>(m_Grid.GetWidth() * BlockSize), static_cast<float_t>(m_Grid.GetHeight() * BlockSize) },
        Mountain::Color::Gray()
    );

    Mountain::Renderer::PopRenderTarget();

    Mountain::Draw::RenderTarget(m_RenderTarget);

    ImGui::Begin("Debug");
    ImGui::SeparatorText("Debug");
    ImGui::Text(
        "FPS: %.1f, DT: %.3f, RDT: %f",
        1.f / Mountain::Time::GetDeltaTime(),
        Mountain::Time::GetDeltaTime(),
        Mountain::Time::GetTargetDeltaTime() - Mountain::Time::GetLastFrameDuration()
    );
    bool_t fullscreen = Mountain::Window::GetFullscreen();
    ImGui::Checkbox("Fullscreen", &fullscreen);
    Mountain::Window::SetFullscreen(fullscreen);
    ImGui::DragFloat2("Camera position", m_Camera.position.Data());
    if (ImGui::Button("-"))
        m_Camera.ZoomOut();
    ImGui::SameLine();
    ImGui::Text("Zoom: %.2f", m_Camera.GetZoom());
    ImGui::SameLine();
    if (ImGui::Button("+"))
        m_Camera.ZoomIn();
    ImGui::SameLine();
    if (ImGui::Button("Reset"))
        m_Camera.SetZoom(1.f);

    const Vector2 mousePos = Mountain::Input::GetMousePosition();
    const Vector2 mousePosWorld = m_Camera.ToWorld(mousePos);
    ImGui::Text("Mouse position: %.2f, %.2f - To world: %.2f, %.2f", mousePos.x, mousePos.y, mousePosWorld.x, mousePosWorld.y);
    const uint64_t x = static_cast<uint64_t>(mousePosWorld.x), y = static_cast<uint64_t>(mousePosWorld.y);
    const uint64_t blockX = x / BlockSize, blockY = y / BlockSize;
    ImGui::Text("Mouse block empty (not updated): %s", m_Grid.GetBlock(blockX, blockY).GetEmpty() ? "true" : "false");

    ImGui::SeparatorText("Game");
    ImGui::Checkbox("Automatically update", &m_AutoUpdate);
    if (ImGui::Button("Update"))
        m_ManualUpdate = true;
    ImGui::DragFloat("Update interval", &m_UpdateInterval, 0.01f, 0.f, std::numeric_limits<float_t>::max());
    ImGui::End();
}

void GameOfLife::Shutdown()
{
    Game::Shutdown();
}
