#include "ball.hpp"

#include <draw.hpp>
#include <renderer.hpp>
#include <circle.hpp>

test::Ball::Ball(const Vector2& position, const mountain::Color color)
	: Entity(position), color(color)
{
	mCollider = new mountain::Circle(0, 3);
	mCollider->SetEntity(this);
}

void test::Ball::Update(const float deltaTime)
{
	mPosition += velocity * deltaTime;
	velocity.y += 100 * deltaTime;

	mCollider->SetPosition(mPosition);
}

void test::Ball::Draw()
{
	mountain::Draw::CircleFilled(mPosition, 3, color);
}
