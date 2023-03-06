#pragma once

#include <game.hpp>

namespace test
{
	class GameExample : public mountain::Game
	{
	public:
		virtual void Update() override;
		virtual void Render() override;
	};
}
