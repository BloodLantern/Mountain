#pragma once

#include <Mountain/Ecs/Entity.hpp>
#include <Mountain/Ecs/Component/Sprite.hpp>

#include "Scenes/TestScene.hpp"

class SpriteAnimationsScene : public TestScene
{
public:
    using Base = TestScene;

    SpriteAnimationsScene();

    void Render() override;

    void RenderImGui() override;

    void LoadResources() override;

    void UnloadResources() override;

private:
    Entity* m_Entity = nullptr;
    Sprite* m_Sprite = nullptr;
};
