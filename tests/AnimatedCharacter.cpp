#include "AnimatedCharacter.hpp"

#include "Mountain/Ecs/Component/Sprite.hpp"
#include "Mountain/Rendering/Draw.hpp"

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
