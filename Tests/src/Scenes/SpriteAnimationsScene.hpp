#pragma once

#include "Common.hpp"

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

    float_t m_Rotation = 0;
    Vector2 m_Origin = Vector2::One() * 0.5f;
};
