#include "Common.hpp"

#include "Scenes/ParticleSystemScene.hpp"

#include <Mountain/Window.hpp>
#include <Mountain/FileSystem/FileManager.hpp>

#include "TestGame.hpp"

ParticleSystemScene::ParticleSystemScene()
    : Base{"Particle System"}
{
    m_ParticleSystem.position = Window::GetSize() * 0.5f;
    m_ParticleSystem.AddModules(ParticleSystemModules::Types::All);
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
