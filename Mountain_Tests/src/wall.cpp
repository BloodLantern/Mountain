#include "wall.hpp"

#include <hitbox.hpp>
#include <draw.hpp>

test::Wall::Wall(const Vector2& position, const Vector2& size)
	: Entity(position), mSize(size)
{
	Collider = new mountain::Hitbox(position, size);
	Collider->Owner = this;
	Collider = new mountain::Hitbox(position, size);
	Collider->Owner = this;
}

void test::Wall::Update(const float)
{
	Collider->Position = Position;
}

void test::Wall::Draw()
{
	mountain::Draw::RectFilled(Position, mSize, mountain::ColorGray);
}
