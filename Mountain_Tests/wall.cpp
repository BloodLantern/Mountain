#include "wall.hpp"

#include <hitbox.hpp>
#include <draw.hpp>

test::Wall::Wall(const Vector2& position, const Vector2& size)
	: Entity(position), mSize(size)
{
	mCollider = new mountain::Hitbox(position, size);
	mCollider->SetEntity(this);
}

void test::Wall::Update(const float)
{
}

void test::Wall::Draw()
{
	mountain::Draw::RectFilled(mPosition, mSize, mountain::ColorGray);
}
