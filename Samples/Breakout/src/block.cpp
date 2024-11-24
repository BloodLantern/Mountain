#include "block.hpp"

#include <Mountain/collision/hitbox.hpp>

#include "Mountain/rendering/draw.hpp"

Block::Block(Ball& ball)
    : m_Ball(&ball)
{
    m_Collider = new Mountain::Hitbox{ Vector2::One() * -BlockSize * 0.5f, Vector2::One() * BlockSize };
    m_Collider->basePosition = &position;
}

Block::~Block()
{
    delete m_Collider;
}

void Block::Update()
{
    Entity::Update();

    CheckBallCollisions();
}

void Block::Render()
{
    Entity::Render();

    Mountain::Draw::RectangleFilled(m_Collider->AbsoluteTopLeft(), Vector2::One() * BlockSize, Mountain::Color::Gray());
}

void Block::RenderDebug()
{
    Entity::RenderDebug();

    m_Collider->RenderDebug(Mountain::Color::Red());
}

void Block::CheckBallCollisions() const
{
    const Mountain::Collider& ballCollider = *m_Ball->GetCollider();
    if (!m_Collider->CheckCollision(ballCollider))
        return;

    const Vector2 diff = ballCollider.AbsoluteCenter() - position;
    if (diff.x > diff.y)
        m_Ball->velocity.x *= -1.f;
    else
        m_Ball->velocity.y *= -1.f;
}
