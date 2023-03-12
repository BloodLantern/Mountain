#pragma once

#include <entity.hpp>
#include <color.hpp>

namespace test
{
	class Wall : public mountain::Entity
	{
	public:
		mountain::Color Color = mountain::ColorGray;

		Wall(const Vector2& position, const Vector2& size);

		// Inherited via Entity
		virtual void Update(const float deltaTime) override;
		virtual void Draw() override;

	private:
		Vector2 mSize;
	};
}
