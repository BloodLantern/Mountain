#pragma once

#include "Mountain/Collision/Collider.hpp"

#include "Mountain/Containers/List.hpp"

namespace Mountain
{
	class ColliderList : public Collider
	{
	public:
		List<Collider*> list;

		MOUNTAIN_API ColliderList();
		MOUNTAIN_API ColliderList(std::initializer_list<Collider*> elements);
		MOUNTAIN_API ColliderList(const Vector2& position, std::initializer_list<Collider*> elements);

		MOUNTAIN_API void RenderDebug(const Color& color) const override;

		ATTRIBUTE_NODISCARD
		MOUNTAIN_API bool CheckCollision(Vector2 point) const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API bool CheckCollision(const Hitbox& hitbox) const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API bool CheckCollision(const Circle& circle) const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API bool CheckCollision(const Grid& grid) const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API bool CheckCollision(const ColliderList& otherList) const override;

		ATTRIBUTE_NODISCARD
		MOUNTAIN_API float_t Left() const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API float_t Right() const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API float_t Top() const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API float_t Bottom() const override;

		ATTRIBUTE_NODISCARD
		MOUNTAIN_API float AbsoluteLeft() const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API float AbsoluteRight() const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API float AbsoluteTop() const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API float AbsoluteBottom() const override;
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API Vector2 AbsoluteCenter() const override;
	};
}
