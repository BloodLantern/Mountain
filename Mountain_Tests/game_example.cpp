#include "game_example.hpp"

#include "ball.hpp"
#include "wall.hpp"

#include <collide.hpp>
#include <draw.hpp>
#include <entity.hpp>
#include <iostream>
#include <typeinfo>

test::GameExample::GameExample(const char* const windowTitle)
	: Game(windowTitle)
{
}

void test::GameExample::Initialize()
{
	ballCount = 0;

	mEntities.push_back((mountain::Entity*) new Wall(Vector2(0, 0), Vector2(100, (float) mRenderer.windowSize.y)));
	mEntities.push_back((mountain::Entity*) new Wall(Vector2((float) mRenderer.windowSize.x - 100, 0), Vector2(100, (float) mRenderer.windowSize.y)));
	mEntities.push_back((mountain::Entity*) new Wall(Vector2(0, (float) mRenderer.windowSize.y - 100), Vector2((float) mRenderer.windowSize.x, 100)));
}

void test::GameExample::Shutdown()
{
	for (std::vector<mountain::Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
		delete* it;
	mEntities.clear();
}

void ColliderCallback(mountain::Entity& entity, mountain::Entity& other)
{
	bool entityWall = typeid(entity) == typeid(test::Wall&), otherWall = typeid(other) == typeid(test::Wall&);
	if (entityWall && otherWall)
		return;

	const Vector2 distance = other.GetPosition() - entity.GetPosition();
	if (!entityWall)
		dynamic_cast<test::Ball&>(entity).velocity = -distance.Normalize() * 10;
	if (!otherWall)
		dynamic_cast<test::Ball&>(entity).velocity = distance.Normalize() * 10;
}

void test::GameExample::Update()
{
	std::vector<const mountain::Collider*> colliders(mEntities.size());
	for (std::vector<mountain::Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
	{
		colliders.push_back((*it)->GetCollider());
		(*it)->Update(mDeltaTime);
	}

	ballTimer -= mDeltaTime;

	if (ballCount < 2000 && ballTimer <= 0)
	{
		lastBallColor.h++;
		Ball* ball = new Ball(Vector2(150, 150), lastBallColor);
		ball->velocity = Vector2(350, 0);
		mEntities.push_back(ball);
		ballCount++;
		ballTimer = 0.8f;
	}

	mountain::Collide::CheckCollisions(colliders, ColliderCallback);
}

void test::GameExample::Render()
{
	for (std::vector<mountain::Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
		(*it)->Draw();
}
