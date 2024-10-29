#include "ball.hpp"

#include <Mountain/window.hpp>
#include <Mountain/collision/circle.hpp>
#include <Mountain/input/time.hpp>
#include <Mountain/rendering/draw.hpp>

#include "Mountain/utils/random.hpp"

Ball::Ball()
{
    m_Collider = new Mountain::Circle{ Vector2::Zero(), BallRadius };
    m_Collider->basePosition = &position;

    position = Mountain::Window::GetSize() * 0.5f;

    velocity = Mountain::Random::Direction() * BallMovementSpeed;
}

Ball::~Ball()
{
    delete m_Collider;
}

Ball::Ball(Ball&& other) noexcept
{
    m_Collider = other.m_Collider;
    // Avoid collider deletion from other destructor
    other.m_Collider = nullptr;
}

Ball& Ball::operator=(Ball&& other) noexcept
{
    m_Collider = other.m_Collider;
    // Avoid collider deletion from other destructor
    other.m_Collider = nullptr;
    return *this;
}

void Ball::Update()
{
    Entity::Update();

    position += velocity * Mountain::Time::GetDeltaTime();

    // Collide with the window bounds
    const Vector2 windowSize = Mountain::Window::GetSize();
    if (m_Collider->AbsoluteBottom() > windowSize.y)
    {
        velocity = Vector2::Zero(); // TODO - Lose/Spawn another ball
    }
    else if (m_Collider->AbsoluteTop() < 0.f)
    {
        velocity.y *= -1.f;
        position.y = BallRadius;
    }
    
    if (m_Collider->AbsoluteLeft() < 0.f)
    {
        velocity.x *= -1.f;
        position.x = BallRadius;
    }
    else if (m_Collider->AbsoluteRight() > windowSize.x)
    {
        velocity.x *= -1.f;
        position.x = windowSize.x - BallRadius;
    }
}

void Ball::Render()
{
    Entity::Render();

    Mountain::Draw::CircleFilled(position, BallRadius);
}

void Ball::RenderDebug()
{
    Entity::RenderDebug();

    m_Collider->RenderDebug(Mountain::Color::Red());
}
