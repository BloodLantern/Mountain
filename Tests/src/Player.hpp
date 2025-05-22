#pragma once

#include "Mountain/Ecs/Entity.ixx"
#include "Mountain/Ecs/Component/Sprite.ixx"
#include "Mountain/Rendering/LightSource.ixx"
#include "Mountain/Utils/Pointer.ixx"

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
