#include "Scenes/ParticleSystemScene.hpp"

#include <Mountain/Window.hpp>

#include "TestGame.hpp"

ParticleSystemScene::ParticleSystemScene()
    : Base{"Particle System"}
{
    m_ParticleSystem.position = Window::GetSize() * 0.5f;
    m_ParticleSystem.modules.AddRange(
        std::make_shared<ParticleSystemModules::Shape>(),
        std::make_shared<ParticleSystemModules::ColorOverLifetime>(),
        std::make_shared<ParticleSystemModules::ForceOverLifetime>()
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
