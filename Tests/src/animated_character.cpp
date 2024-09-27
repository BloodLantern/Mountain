#include "animated_character.hpp"

#include "Mountain/rendering/draw.hpp"
#include "Mountain/scene/component/sprite.hpp"

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
