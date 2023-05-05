#include "game_example.hpp"

#include "ball.hpp"
#include "wall.hpp"

#include <collide.hpp>
#include <draw.hpp>
#include <entity.hpp>
#include <renderer.hpp>
#include <input.hpp>

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

test::GameExample::GameExample(const char* const windowTitle)
	: Game(windowTitle),
	grid(Vector2i(10, 10), Vector2(64, 64), Vector2(150))
{
}

void InitializeImGui()
{
    // Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(mountain::Renderer::GetWindow(), true);
	ImGui_ImplOpenGL3_Init(mountain::Renderer::GetOpenGLVersion().glsl);
}

void ShutdownImGui()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

test::Ball* cursor = new test::Ball(0, mountain::ColorWhite, 20);

void test::GameExample::Initialize()
{
	InitializeImGui();

	ballCount = 0;

	Entities.push_back(new Wall(Vector2(0, FLT_MIN), Vector2(100, (float) mountain::Renderer::WindowSize.y)));
	Entities.push_back(new Wall(Vector2((float) mountain::Renderer::WindowSize.x - 100, FLT_MIN), Vector2(100, (float) mountain::Renderer::WindowSize.y)));
	Entities.push_back(new Wall(Vector2(0, (float)mountain::Renderer::WindowSize.y - 100), Vector2((float)mountain::Renderer::WindowSize.x, 100)));

	cursor->Collides = false;
	Entities.push_back(cursor);

	grid.Tiles[0][0] = true;
	grid.Tiles[0][1] = true;
	grid.Tiles[1][0] = true;
	grid.Tiles[1][1] = true;
	grid.Tiles[1][2] = true;
	grid.Tiles[1][3] = true;
	grid.Tiles[2][3] = true;
	grid.Tiles[4][3] = true;
}

void test::GameExample::Shutdown()
{
	for (std::vector<mountain::Entity*>::iterator it = Entities.begin(); it != Entities.end(); it++)
		delete* it;

	ShutdownImGui();
}

void test::GameExample::PreRender()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void test::GameExample::PostRender()
{
    // End ImGui frame
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(mountain::Renderer::GetWindow(), &display_w, &display_h);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

void ResolveCollision(test::Ball& ball, const test::Wall& other)
{
	if (!ball.Collides)
		return;

	const Vector2 difference = ball.Collider->Center() - other.Collider->Center();
	const Vector2 minDist = ball.Collider->Size() / 2 + other.Collider->Size() / 2;
	const Vector2 depth(difference.x > 0 ? minDist.x - difference.x : -minDist.x - difference.x,
		difference.y > 0 ? minDist.y - difference.y : -minDist.y - difference.y);

	if (std::abs(depth.x) < std::abs(depth.y))
	{
		ball.Position.x += depth.x;
		ball.Velocity.x *= -0.85f;
	}
	else
	{
		ball.Position.y += depth.y;
		ball.Velocity.y *= -0.85f;
	}
	ball.Collider->Position = ball.Position;
}

void ResolveCollision(test::Ball& ball, test::Ball& other)
{
	if (!ball.Collides)
		return;

	Vector2 distance = (other.Collider->Center() - ball.Collider->Center()).Normalized();
	const Vector2 minDist = ball.Collider->Size() / 2 + other.Collider->Size() / 2;
	ball.Position = other.Position - distance * minDist;
	ball.Collider->Position = ball.Position;
	
	Vector2 relativeVelocity = other.Velocity - ball.Velocity;
	float relativeSpeed = relativeVelocity.Dot(distance);
	Vector2 impulse = -1 * relativeSpeed * distance;
	ball.Velocity -= impulse;
	other.Velocity += impulse;
}

void ColliderCallback(mountain::Entity& entity, mountain::Entity& other)
{
	const bool entityWall = entity.Type == 0, otherWall = other.Type == 0;
	if (entityWall && otherWall)
		return;

	if (!entityWall)
	{
		test::Ball& ballEntity = dynamic_cast<test::Ball&>(entity);
		if (otherWall)
			ResolveCollision(ballEntity, dynamic_cast<test::Wall&>(other));
		else
			ResolveCollision(ballEntity, dynamic_cast<test::Ball&>(other));
	}
	if (!otherWall)
	{
		test::Ball& ballOther = dynamic_cast<test::Ball&>(other);
		if (entityWall)
			ResolveCollision(ballOther, dynamic_cast<test::Wall&>(entity));
		else
			ResolveCollision(ballOther, dynamic_cast<test::Ball&>(entity));
	}
}

bool throwBalls = false;
int maxBalls = 10;
float ballSpawnDelay = 0.05f;

void test::GameExample::Update()
{
	double x, y;
	glfwGetCursorPos(mountain::Renderer::GetWindow(), &x, &y);
	cursor->Position = Vector2((float) x, (float) y);

	cursor->Velocity = 0;

	std::vector<const mountain::Collider*> colliders(Entities.size());
	for (std::vector<mountain::Entity*>::iterator it = Entities.begin(); it != Entities.end(); it++)
	{
		colliders.push_back((*it)->Collider);
		(*it)->Update(DeltaTime);
	}

	ballTimer -= DeltaTime;

	if (throwBalls)
		if (ballCount < maxBalls && ballTimer <= 0)
		{
			lastBallColor.h++;
			Ball* ball = new Ball(Vector2(150, 150), lastBallColor);
			ball->Velocity = Vector2(350, 0);
			Entities.push_back(ball);
			ballCount++;
			ballTimer = ballSpawnDelay;
		}

	mountain::Collide::CheckCollisions(colliders, ColliderCallback);
}

bool showInputs = false;

void test::GameExample::Render()
{
	/*for (std::vector<mountain::Entity*>::iterator it = Entities.begin(); it != Entities.end(); it++)
	{
		(*it)->Draw();
		//(*it)->Collider->Draw(mountain::ColorRed);
	}*/

	grid.Draw(mountain::ColorRed);

	ImGui::Begin("Debug");
	ImGui::Checkbox("Throw balls", &throwBalls);
	ImGui::Checkbox("Show inputs window", &showInputs);
	ImGui::InputInt("Max balls", &maxBalls);
	ImGui::InputFloat("Ball spawn delay", &ballSpawnDelay);
	ImGui::End();

	if (showInputs)
	{
		ImGui::Begin("Inputs");
		if (ImGui::TreeNode("Mouse"))
		{
			ImGui::Text("Position: %d, %d", mountain::Input::MousePosition.x, mountain::Input::MousePosition.y);
			ImGui::Text("Button down right: %d", mountain::Input::MouseDown[mountain::inputs::MouseButton_Right]);
			ImGui::Text("Button release right: %d", mountain::Input::MouseRelease[mountain::inputs::MouseButton_Right]);
			for (unsigned char i = 0; i < mountain::inputs::MouseButton_MaxCount; i++)
			{
				ImGui::Text("Button down %d: %d", i + 1, mountain::Input::MouseDown[i]);
				ImGui::Text("Button release %d: %d", i + 1, mountain::Input::MouseRelease[i]);
			}
			ImGui::Text("Wheel: %f, %f", mountain::Input::MouseWheel.x, mountain::Input::MouseWheel.y);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Keyboard"))
		{
			ImGui::Text("Key down B: %d", mountain::Input::KeyboardKeyDown[mountain::inputs::KeyboardKey_B]);
			ImGui::Text("Key release B: %d", mountain::Input::KeyboardKeyRelease[mountain::inputs::KeyboardKey_B]);
			ImGui::TreePop();
		}

		ImGui::Text("Controllers connected: %u", mountain::Input::ControllerConnectedCount);
		for (unsigned char i = 0; i < mountain::Input::ControllerConnectedCount; i++)
		{
			char nameBuffer[14];
			sprintf_s(nameBuffer, "Controller %u", i + 1);
			if (ImGui::TreeNode(nameBuffer))
			{
				ImGui::Text("Left stick axis: %f, %f",
					mountain::Input::ControllerStickAxis[i][mountain::inputs::Controller_StickLeft].x,
					mountain::Input::ControllerStickAxis[i][mountain::inputs::Controller_StickLeft].y);
				ImGui::Text("Right stick axis: %f, %f",
					mountain::Input::ControllerStickAxis[i][mountain::inputs::Controller_StickRight].x,
					mountain::Input::ControllerStickAxis[i][mountain::inputs::Controller_StickRight].y);
				
				ImGui::Text("Left trigger axis: %f", mountain::Input::ControllerTriggerAxis[i][mountain::inputs::Controller_TriggerLeft]);
				ImGui::Text("Right trigger axis: %f", mountain::Input::ControllerTriggerAxis[i][mountain::inputs::Controller_TriggerRight]);

				for (unsigned char j = 0; j < mountain::inputs::Controller_ButtonCount; j++)
					ImGui::Text("Button %d: %d", j + 1, mountain::Input::ControllerButton[i][j]);

				ImGui::Text("Directional pad direction: %u", mountain::Input::ControllerDirectionalPad[i]);
				
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}
}
