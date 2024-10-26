#include "paddle.hpp"

#include <Mountain/collision/hitbox.hpp>
#include <Mountain/input/input.hpp>
#include <Mountain/rendering/draw.hpp>

#include <ImGui/imgui.h>

Paddle::Paddle(Ball& ball)
    : m_Ball(&ball)
{
    m_Collider = new Mountain::Hitbox{ -PlayerSize * 0.5f, PlayerSize };
    m_Collider->basePosition = &position;
}

Paddle::~Paddle()
{
    delete m_Collider;
}

void Paddle::Update()
{
    Entity::Update();
    
    const Vector2 windowSize = Mountain::Window::GetSize();
    position.x = Calc::Clamp(
        Mountain::Input::GetMousePosition().x,
        PlayerSize.x * 0.5f,
        windowSize.x - PlayerSize.x * 0.5f
    );
    position.y = windowSize.y * 0.95f;

    CheckBallCollisions();
}

void Paddle::Render()
{
    Entity::Render();
    
    Mountain::Draw::RectangleFilled(m_Collider->AbsoluteTopLeft(), PlayerSize);
}

void Paddle::RenderDebug()
{
    Entity::RenderDebug();
    
    m_Collider->RenderDebug(Mountain::Color::Red());
}

void Paddle::RenderImGui()
{
    ImGui::DragFloat2("Position", position.Data());
}

void Paddle::CheckBallCollisions() const
{
    const Mountain::Collider& ballCollider = *m_Ball->GetCollider();
    if (!m_Collider->CheckCollision(ballCollider))
        return;

    float_t distance = m_Ball->position.x - position.x;
    float_t percentage = distance / PlayerSize.x * 0.5f;

    Vector2 newVelocity{ BallMovementSpeed * percentage * 2.f, -1.f * Calc::Abs(m_Ball->velocity.y) };
    m_Ball->velocity = newVelocity.Normalized() * m_Ball->velocity.Length();
}
