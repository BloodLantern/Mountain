#pragma once

#include "collider.hpp"

#include <vector>

namespace mountain
{
	class ColliderList : public Collider
	{
	public:
		std::vector<Collider*> list;

		ColliderList() { Type = ColliderType::List; }
		ColliderList(std::initializer_list<Collider*> elements);
		ColliderList(const Vector2& position, std::initializer_list<Collider*> elements);

		void Draw(const Color color) const override;

		bool CheckCollision(const Vector2& point) const override;
		bool CheckCollision(const Hitbox& hitbox) const override;
		bool CheckCollision(const Circle& circle) const override;
		bool CheckCollision(const Grid& grid) const override;
		bool CheckCollision(const ColliderList& otherList) const override;

		float Left() const override;
		float Right() const override;
		float Top() const override;
		float Bottom() const override;
		Vector2 Center() const override;
	};
}
