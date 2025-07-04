#pragma once

#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Ecs/Component/Sprite.hpp"

class AnimatedCharacter : public Mountain::Entity
{
public:
    explicit AnimatedCharacter(Vector2 pos);
    
    void Render() override;

private:
    Mountain::Sprite* m_Sprite;
};
