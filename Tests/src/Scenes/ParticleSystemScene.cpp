#include "Scenes/ParticleSystemScene.hpp"

#include <Mountain/Window.hpp>

#include "TestGame.hpp"

ParticleSystemScene::ParticleSystemScene()
    : Base{"ParticleSystem"}
{
    particleSystem.position = Mountain::Window::GetSize() * 0.5f;
    particleSystem.modules.AddRange(
        std::make_shared<Mountain::ParticleSystemModules::Shape>(),
        std::make_shared<Mountain::ParticleSystemModules::ColorOverLifetime>(),
        std::make_shared<Mountain::ParticleSystemModules::ForceOverLifetime>()
    );
}

void ParticleSystemScene::Update()
{
    TestScene::Update();

    particleSystem.Update();
}

void ParticleSystemScene::Render()
{
    TestScene::Render();

    particleSystem.Render();
}

void ParticleSystemScene::RenderDebug()
{
    TestScene::RenderDebug();

    particleSystem.RenderDebug();
}

void ParticleSystemScene::RenderImGui()
{
    TestScene::RenderImGui();

    particleSystem.RenderImGui();
}
