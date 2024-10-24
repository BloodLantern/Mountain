#include "player.hpp"

#include <Mountain/collision/hitbox.hpp>
#include <Mountain/input/input.hpp>
#include <Mountain/rendering/draw.hpp>

#include <ImGui/imgui.h>

Player::Player(Ball& ball)
    : ball(&ball)
{
    m_Collider = new Mountain::Hitbox{ -PlayerSize * 0.5f, PlayerSize };
    m_Collider->basePosition = &position;
}

Player::~Player()
{
    delete m_Collider;
}

void Player::Update()
{
    Entity::Update();
    
    const Vector2 windowSize = Mountain::Window::GetSize();
    position.x = Calc::Clamp(
        Mountain::Input::GetMousePosition().x,
        PlayerSize.x * 0.5f,
        windowSize.x - PlayerSize.x * 0.5f
    );
    position.y = windowSize.y * 0.95f;
}

void Player::Render()
{
    Entity::Render();
    
    Mountain::Draw::RectangleFilled(m_Collider->AbsoluteTopLeft(), PlayerSize);
}

void Player::RenderDebug()
{
    Entity::RenderDebug();
    
    m_Collider->RenderDebug(Mountain::Color::Red());
}

void Player::RenderImGui()
{
    ImGui::DragFloat2("Position", position.Data());
}
