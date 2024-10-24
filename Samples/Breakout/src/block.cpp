#include "block.hpp"

#include <Mountain/collision/hitbox.hpp>

#include "Mountain/rendering/draw.hpp"

Block::Block()
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
