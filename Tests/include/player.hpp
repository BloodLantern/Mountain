#pragma once

#include "Mountain/resource/texture.hpp"
#include "Mountain/scene/entity.hpp"
#include "Mountain/scene/component/light_source.hpp"
#include "Mountain/scene/component/sprite.hpp"
#include "Mountain/utils/pointer.hpp"

class Player : public Mountain::Entity
{
public:
    float_t movementSpeed = 150.f;

    Mountain::LightSource* light;
    Mountain::Sprite* sprite;
    
    Player(const Vector2& pos, Mountain::LightSource& lightSource);

    void LoadResources();
    void Update() override;
    void Render() override;
};
