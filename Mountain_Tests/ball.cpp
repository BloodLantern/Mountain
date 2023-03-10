#include "ball.hpp"

#include <draw.hpp>
#include <renderer.hpp>
#include <circle.hpp>

test::Ball::Ball(const Vector2& position, const mountain::Color color)
	: Entity(position), color(color)
{
	Collider = new mountain::Circle(0, 3);
	Collider->SetEntity(this);
}

void test::Ball::Update(const float deltaTime)
{
	Position += velocity * deltaTime;
	velocity.y += 100 * deltaTime;

	Collider->SetPosition(Position);
}

void test::Ball::Draw()
{
	mountain::Draw::CircleFilled(Position, 3, color);
}
