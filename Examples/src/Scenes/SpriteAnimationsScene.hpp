#pragma once

#include "PrecompiledHeader.hpp"

#include <Mountain/Ecs/Entity.hpp>
#include <Mountain/Ecs/Component/Sprite.hpp>

#include "Scenes/TestScene.hpp"

class SpriteAnimationsScene : public TestScene
{
public:
    using Base = TestScene;

    SpriteAnimationsScene();

    void LoadPersistentResources() override;

    void Render() override;

    void RenderImGui() override;

private:
    Entity* m_Entity = nullptr;
    Sprite* m_Sprite = nullptr;

    f32 m_Rotation = 0.f;
    Vector2 m_Origin = Vector2::One() * 0.5f;
};
