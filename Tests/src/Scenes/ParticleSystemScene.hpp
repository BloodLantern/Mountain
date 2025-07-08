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

private:
	Mountain::ParticleSystem m_ParticleSystem{ 1000 };
};
