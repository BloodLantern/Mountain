#pragma once

#include <Mountain/Rendering/ParticleSystem.hpp>

#include "Scenes/TestScene.hpp"

class ParticleSystemScene : public TestScene
{
public:
	using Base = TestScene;

	Mountain::ParticleSystem particleSystem{ 1000 };

	ParticleSystemScene();

	void Update() override;

	void Render() override;

	void RenderDebug() override;

	void RenderImGui() override;
};
