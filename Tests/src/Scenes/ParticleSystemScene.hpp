#pragma once

#include <Mountain/Rendering/ParticleSystem.hpp>

#include "Scenes/TestScene.hpp"

class ParticleSystemScene : public TestScene
{
public:
	using Base = TestScene;

	ParticleSystemScene();

	void Update() override;

	void Render() override;

	void RenderDebug() override;

	void RenderImGui() override;

	void LoadResources() override;

	void UnloadResources() override;

private:
	ParticleSystem m_ParticleSystem{ 1000 };
};
