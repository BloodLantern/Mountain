#pragma once

#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Ecs/Component/Sprite.hpp"
#include "Mountain/Rendering/LightSource.hpp"
#include "Mountain/Utils/Pointer.hpp"

class Player : public Mountain::Entity
{
public:
    float_t movementSpeed = 150.f;

    Mountain::LightSource* light;
    Mountain::Sprite* sprite;

    explicit Player(const Vector2& pos, Mountain::LightSource& lightSource);

    void LoadResources();
    void Update() override;
    void Render() override;
};
