#pragma once

#include "Mountain/collision/collider.hpp"

#include "Mountain/utils/list.hpp"

BEGIN_MOUNTAIN

class ColliderList : public Collider
{
public:
	List<Collider*> list;

	MOUNTAIN_API ColliderList();
	MOUNTAIN_API ColliderList(std::initializer_list<Collider*> elements);
	MOUNTAIN_API ColliderList(const Vector2& position, std::initializer_list<Collider*> elements);

	MOUNTAIN_API void DebugRender(const Color& color) const override;

	[[nodiscard]]
	MOUNTAIN_API bool CheckCollision(const Vector2& point) const override;
	[[nodiscard]]
	MOUNTAIN_API bool CheckCollision(const Hitbox& hitbox) const override;
	[[nodiscard]]
	MOUNTAIN_API bool CheckCollision(const Circle& circle) const override;
	[[nodiscard]]
	MOUNTAIN_API bool CheckCollision(const Grid& grid) const override;
	[[nodiscard]]
	MOUNTAIN_API bool CheckCollision(const ColliderList& otherList) const override;

	[[nodiscard]]
	MOUNTAIN_API float Left() const override;
	[[nodiscard]]
	MOUNTAIN_API float Right() const override;
	[[nodiscard]]
	MOUNTAIN_API float Top() const override;
	[[nodiscard]]
	MOUNTAIN_API float Bottom() const override;
	[[nodiscard]]
	MOUNTAIN_API Vector2 Center() const override;
};

END_MOUNTAIN
