#include "breakout.hpp"

#include <ImGui/imgui.h>

#include <Mountain/window.hpp>
#include <Mountain/rendering/draw.hpp>
#include <Mountain/utils/color.hpp>

Breakout::Breakout()
    : Game("Mountain sample project - Breakout", { 1280, 720 })
    , m_Paddle(m_Ball)
{
}

void Breakout::Initialize()
{
    Game::Initialize();

    const Vector2 windowSize = Mountain::Window::GetSize();

    static constexpr int32_t BlockCount = 10;
    for (int32_t i = 0; i < BlockCount; ++i)
    {
        Block* block = new Block(m_Ball);
        m_Blocks.Add(block);
        block->position = { windowSize.x * 0.5f + static_cast<float_t>(i - BlockCount / 2) * BlockSize, windowSize.y * 0.1f };  // NOLINT(bugprone-integer-division)
    }
}

void Breakout::Shutdown()
{
    for (const Block* const block : m_Blocks)
        delete block;

    Game::Shutdown();
}

void Breakout::Update()
{
    m_Ball.Update();

    for (Block* const block : m_Blocks)
        block->Update();
    
    m_Paddle.Update();
}

void Breakout::Render()
{
    Mountain::Draw::Clear(Mountain::Color::CornflowerBlue());

    m_Ball.Render();
    
    for (Block* const block : m_Blocks)
        block->Render();

    m_Paddle.Render();

    if (m_ShowHitboxes)
    {
        m_Ball.RenderDebug();
    
        for (Block* const block : m_Blocks)
            block->RenderDebug();
        
        m_Paddle.RenderDebug();
    }

    RenderImGui();
}

void Breakout::RenderImGui()
{
    ImGui::Begin("Player");
    m_Paddle.RenderImGui();
    ImGui::End();

    ImGui::Begin("Debug");
    ImGui::Checkbox("Show hitboxes", &m_ShowHitboxes);
    if (ImGui::Button("Reset"))
    {
        m_Ball = {};
    }
    ImGui::End();
}
