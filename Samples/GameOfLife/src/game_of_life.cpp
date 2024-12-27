#include "game_of_life.hpp"

#include "ImGui/imgui.h"
#include "Mountain/input/input.hpp"
#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/rendering/renderer.hpp"

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

        if (Mountain::Input::GetMouseButton(Mountain::MouseButton::Left, Mountain::MouseButtonStatus::Pressed))
        {
            const Vector2 pos = m_Camera.ToWorld(Mountain::Input::GetMousePosition());
            const uint64_t x = static_cast<uint64_t>(pos.x), y = static_cast<uint64_t>(pos.y);
            m_Grid.ToggleCell(x / BlockSize, y / BlockSize, x % BlockSize, y % BlockSize);
        }

        if (Mountain::Input::GetKey(Mountain::Key::Escape))
            Mountain::Window::SetShouldClose(true);
    }

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
