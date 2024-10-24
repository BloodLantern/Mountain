#include "ball.hpp"

#include <Mountain/window.hpp>
#include <Mountain/collision/circle.hpp>
#include <Mountain/input/time.hpp>
#include <Mountain/rendering/draw.hpp>

#include "Mountain/utils/random.hpp"

Ball::Ball()
{
    m_Collider = new Mountain::Circle{ Vector2::Zero(), BallSize };
    m_Collider->basePosition = &position;

    position = Mountain::Window::GetSize() * 0.5f;

    velocity = Mountain::Random::Direction() * BallMovementSpeed;
}

Ball::~Ball()
{
    delete m_Collider;
}

void Ball::Update()
{
    Entity::Update();

    position += velocity * Mountain::Time::GetDeltaTime();

    // Collide with the window bounds
    const Vector2 windowSize = Mountain::Window::GetSize();
    if (m_Collider->AbsoluteTop() < 0.f || m_Collider->AbsoluteBottom() > windowSize.y)
        velocity.y *= -1.f;
    if (m_Collider->AbsoluteLeft() < 0.f || m_Collider->AbsoluteRight() > windowSize.x)
        velocity.x *= -1.f;
}

void Ball::Render()
{
    Entity::Render();

    Mountain::Draw::CircleFilled(position, BallSize);
}

void Ball::RenderDebug()
{
    Entity::RenderDebug();

    m_Collider->RenderDebug(Mountain::Color::Red());
}
