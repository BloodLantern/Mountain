#pragma once

#include <include/game.hpp>
#include <include/color.hpp>
#include <include/grid.hpp>
#include <include/texture.hpp>

namespace test
{
	class GameExample : public mountain::Game
	{
	public:
        std::vector<mountain::Entity*> Entities;
		int ballCount = 0;
		float ballTimer = 0;
		mountain::ColorHSV lastBallColor = mountain::Color::Red;
		mountain::Texture texture = mountain::Texture("assets/strawberry.png");

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
