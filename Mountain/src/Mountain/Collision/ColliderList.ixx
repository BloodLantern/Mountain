export module Mountain:Collision_ColliderList;

import "Mountain/Core.hpp";

export import :Collision_Collider;
export import :Utils_List;

export namespace Mountain
{
	class ColliderList : public Collider
	{
	public:
		List<Collider*> list;

		MOUNTAIN_API ColliderList();
		MOUNTAIN_API ColliderList(std::initializer_list<Collider*> elements);
		MOUNTAIN_API ColliderList(const Vector2& position, std::initializer_list<Collider*> elements);

		MOUNTAIN_API void RenderDebug(const Color& color) const override;

		[[nodiscard]]
		MOUNTAIN_API bool CheckCollision(Vector2 point) const override;
		[[nodiscard]]
		MOUNTAIN_API bool CheckCollision(const Hitbox& hitbox) const override;
		[[nodiscard]]
		MOUNTAIN_API bool CheckCollision(const Circle& circle) const override;
		[[nodiscard]]
		MOUNTAIN_API bool CheckCollision(const Grid& grid) const override;
		[[nodiscard]]
		MOUNTAIN_API bool CheckCollision(const ColliderList& otherList) const override;

		[[nodiscard]]
		MOUNTAIN_API float_t Left() const override;
		[[nodiscard]]
		MOUNTAIN_API float_t Right() const override;
		[[nodiscard]]
		MOUNTAIN_API float_t Top() const override;
		[[nodiscard]]
		MOUNTAIN_API float_t Bottom() const override;

		[[nodiscard]]
		MOUNTAIN_API float AbsoluteLeft() const override;
		[[nodiscard]]
		MOUNTAIN_API float AbsoluteRight() const override;
		[[nodiscard]]
		MOUNTAIN_API float AbsoluteTop() const override;
		[[nodiscard]]
		MOUNTAIN_API float AbsoluteBottom() const override;
		[[nodiscard]]
		MOUNTAIN_API Vector2 AbsoluteCenter() const override;
	};
}
