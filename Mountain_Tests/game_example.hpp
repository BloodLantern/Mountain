#pragma once

#include <game.hpp>

namespace test
{
	class GameExample : public mountain::Game
	{
	public:
		unsigned int ballCount = 0;
		float ballTimer = 0;
		mountain::ColorHSV lastBallColor = mountain::ColorRed;

		GameExample(const char* const windowTitle);

		void Initialize() override;
		void Shutdown() override;
		void Update() override;
		void Render() override;
	};
}
