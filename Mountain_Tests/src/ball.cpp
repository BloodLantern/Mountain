#include "ball.hpp"

#include <draw.hpp>
#include <renderer.hpp>
#include <circle.hpp>

test::Ball::Ball(const Vector2& position, const mountain::Color color, const float radius)
	: Entity(position), Color(color)
{
	Collider = new mountain::Circle(0, radius);
	Collider->Owner = this;
}

void test::Ball::Update(const float deltaTime)
{
	Position += Velocity * deltaTime;
	Velocity.y += 100 * deltaTime;

	Collider->Position = Position;
}

void test::Ball::Draw()
{
	mountain::Draw::CircleFilled(Position, Collider->Width() / 2, Color);
}
