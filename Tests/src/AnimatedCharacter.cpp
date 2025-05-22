#include "AnimatedCharacter.hpp"

#include "Mountain/Ecs/Component/Sprite.ixx"
#include "Mountain/Rendering/Draw.ixx"

AnimatedCharacter::AnimatedCharacter(const Vector2 pos)
    : Entity(pos)
{
    m_Sprite = AddComponent<Mountain::Sprite>("assets/oldlady/idle");
}

void AnimatedCharacter::Render()
{
    Entity::Render();

    Mountain::Draw::Texture(*m_Sprite->Get(), position);
}
