#include "Scenes/ParticleSystemScene.hpp"

#include <Mountain/Window.hpp>

#include "TestGame.hpp"

ParticleSystemScene::ParticleSystemScene()
    : Base{"Particle System"}
{
    m_ParticleSystem.position = Mountain::Window::GetSize() * 0.5f;
    m_ParticleSystem.modules.AddRange(
        std::make_shared<Mountain::ParticleSystemModules::Shape>(),
        std::make_shared<Mountain::ParticleSystemModules::ColorOverLifetime>(),
        std::make_shared<Mountain::ParticleSystemModules::ForceOverLifetime>()
    );
}

void ParticleSystemScene::Update()
{
    TestScene::Update();

    m_ParticleSystem.Update();
}

void ParticleSystemScene::Render()
{
    TestScene::Render();

    m_ParticleSystem.Render();
}

void ParticleSystemScene::RenderDebug()
{
    TestScene::RenderDebug();

    m_ParticleSystem.RenderDebug();
}

void ParticleSystemScene::RenderImGui()
{
    TestScene::RenderImGui();

    m_ParticleSystem.RenderImGui();
}
