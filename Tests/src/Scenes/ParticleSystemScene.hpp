#pragma once

#include "Common.hpp"

#include <Mountain/Rendering/ParticleSystem.hpp>

#include "Scenes/TestScene.hpp"

class ParticleSystemScene : public TestScene
{
public:
	using Base = TestScene;

	ParticleSystemScene();

private:
	void Update() override;

	void Render() override;

	void RenderDebug() override;

	void RenderImGui() override;

	ParticleSystem m_ParticleSystem{ 1000 };
};
