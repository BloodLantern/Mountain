#include "game_example.hpp"

#include "ball.hpp"
#include "wall.hpp"

#include <collide.hpp>
#include <draw.hpp>
#include <entity.hpp>
#include <iostream>

test::GameExample::GameExample(const char* const windowTitle)
	: Game(windowTitle)
{
}

test::Ball* cursor = new test::Ball(0, mountain::ColorWhite, 20);

void test::GameExample::Initialize()
{
	ballCount = 0;

	Entities.push_back(new Wall(Vector2(0, 0), Vector2(100, (float) Renderer.WindowSize.y)));
	Entities.push_back(new Wall(Vector2((float) Renderer.WindowSize.x - 100, 0), Vector2(100, (float) Renderer.WindowSize.y)));
	Entities.push_back(new Wall(Vector2(0, (float)Renderer.WindowSize.y - 100), Vector2((float)Renderer.WindowSize.x, 100)));

	cursor->Collides = false;
	Entities.push_back(cursor);
}

void test::GameExample::Shutdown()
{
	for (std::vector<mountain::Entity*>::iterator it = Entities.begin(); it != Entities.end(); it++)
		delete* it;
}

void ResolveCollision(test::Ball& ball, const test::Wall& other)
{
	if (!ball.Collides)
		return;

	const Vector2 difference = ball.Collider->Center() - other.Collider->Center();
	const Vector2 minDist = ball.Collider->Size() / 2 + other.Collider->Size() / 2;
	const Vector2 depth(difference.x > 0 ? minDist.x - difference.x : -minDist.x - difference.x,
		difference.y > 0 ? minDist.y - difference.y : -minDist.y - difference.y);

	//__assume(depth != 0);

	if (std::abs(depth.x) < std::abs(depth.y))
	{
		ball.Position.x += depth.x;
		ball.Velocity.x = -ball.Velocity.x;
	}
	else
	{
		ball.Position.y += depth.y;
		ball.Velocity.y = -ball.Velocity.y;
	}
}

void ResolveCollision(test::Ball& ball, const test::Ball& other)
{
	if (!ball.Collides)
		return;

	const Vector2 difference = ball.Collider->Center() - other.Collider->Center();
	const Vector2 minDist = ball.Collider->Size() / 2 + other.Collider->Size() / 2;
	const Vector2 depth(difference.x > 0 ? minDist.x - difference.x : -minDist.x - difference.x,
		difference.y > 0 ? minDist.y - difference.y : -minDist.y - difference.y);

	//__assume(depth != 0);

	if (std::abs(depth.x) < std::abs(depth.y))
	{
		ball.Position.x += depth.x;
		ball.Velocity.x = -ball.Velocity.x;
		ball.Velocity.y = ball.Velocity.y + (other.Velocity.y - ball.Velocity.y);
	}
	else
	{
		ball.Position.y += depth.y;
		ball.Velocity.x = ball.Velocity.x + (other.Velocity.x - ball.Velocity.x);
		ball.Velocity.y = -ball.Velocity.y;
	}
}

void ColliderCallback(mountain::Entity& entity, mountain::Entity& other)
{
	const bool entityWall = typeid(entity) == typeid(test::Wall&), otherWall = typeid(other) == typeid(test::Wall&);
	if (entityWall && otherWall)
		return;

	if (!entityWall)
	{
		if (otherWall)
			ResolveCollision(dynamic_cast<test::Ball&>(entity), dynamic_cast<test::Wall&>(other));
		else
			ResolveCollision(dynamic_cast<test::Ball&>(entity), dynamic_cast<test::Ball&>(other));
	}
	if (!otherWall)
	{
		if (entityWall)
			ResolveCollision(dynamic_cast<test::Ball&>(other), dynamic_cast<test::Wall&>(entity));
		else
			ResolveCollision(dynamic_cast<test::Ball&>(other), dynamic_cast<test::Ball&>(entity));
	}
}

void test::GameExample::Update()
{
	double x, y;
	glfwGetCursorPos(Renderer.GetWindow(), &x, &y);
	cursor->Position = Vector2((float) x, (float) y);

	cursor->Velocity = 0;

	std::vector<const mountain::Collider*> colliders(Entities.size());
	for (std::vector<mountain::Entity*>::iterator it = Entities.begin(); it != Entities.end(); it++)
	{
		colliders.push_back((*it)->Collider);
		(*it)->Update(DeltaTime);
	}

	ballTimer -= DeltaTime;

	if (ballCount < 2000 && ballTimer <= 0)
	{
		lastBallColor.h++;
		Ball* ball = new Ball(Vector2(150, 150), lastBallColor);
		ball->Velocity = Vector2(350, 0);
		Entities.push_back(ball);
		ballCount++;
		ballTimer = 0.05f;
	}

	mountain::Collide::CheckCollisions(colliders, ColliderCallback);
}

void test::GameExample::Render()
{
	for (std::vector<mountain::Entity*>::iterator it = Entities.begin(); it != Entities.end(); it++)
	{
		(*it)->Draw();
		(*it)->Collider->Draw(mountain::ColorRed);
	}
}
