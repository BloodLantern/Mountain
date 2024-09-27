#pragma once

#include "Mountain/scene/entity.hpp"
#include "Mountain/scene/component/sprite.hpp"

class AnimatedCharacter : public Mountain::Entity
{
public:
    explicit AnimatedCharacter(Vector2 pos);
    
    void Render() override;

private:
    Mountain::Sprite* m_Sprite;
};
