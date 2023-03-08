#pragma once

#include <entity.hpp>

namespace test
{
	class Wall : mountain::Entity
	{
	public:
		Wall(const Vector2& position, const Vector2& size);

		// Inherited via Entity
		virtual void Update(const float deltaTime) override;
		virtual void Draw() override;

	private:
		Vector2 mSize;
	};
}
