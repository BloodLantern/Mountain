#pragma once

#include "Mountain/Ecs/Entity.ixx"
#include "Mountain/Ecs/Component/Sprite.ixx"

class AnimatedCharacter : public Mountain::Entity
{
public:
    explicit AnimatedCharacter(Vector2 pos);
    
    void Render() override;

private:
    Mountain::Sprite* m_Sprite;
};
