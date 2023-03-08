#pragma once

#include <entity.hpp>
#include <color.hpp>

namespace test
{
	class Ball : public mountain::Entity
	{
	public:
		Vector2 velocity;
		mountain::Color color;

		Ball(const Vector2& position, const mountain::Color color);

		// Inherited via Entity
		virtual void Update(const float deltaTime) override;
		virtual void Draw() override;
	};
}
