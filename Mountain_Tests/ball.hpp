#pragma once

#include <entity.hpp>
#include <color.hpp>

namespace test
{
	class Ball : public mountain::Entity
	{
	public:
		Vector2 Velocity;
		mountain::Color Color;
		bool Collides = true;

		Ball(const Vector2& position, const mountain::Color color, const float radius = 3);

		// Inherited via Entity
		virtual void Update(const float deltaTime) override;
		virtual void Draw() override;
	};
}
