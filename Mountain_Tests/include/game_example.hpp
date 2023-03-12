#pragma once

#include <game.hpp>
#include <color.hpp>

namespace test
{
	class GameExample : public mountain::Game
	{
	public:
        std::vector<mountain::Entity*> Entities;
		unsigned int ballCount = 0;
		float ballTimer = 0;
		mountain::ColorHSV lastBallColor = mountain::ColorRed;

		GameExample(const char* const windowTitle);

		// Inherited from Game
		void Initialize() override;
		void Shutdown() override;
		void PreRender() override;
		void PostRender() override;
		void Update() override;
		void Render() override;
	};
}
