#pragma once

#include "Mountain/Game.ixx"
#include "Mountain/Collision/Grid.hpp"
#include "Mountain/Rendering/ParticleSystem.hpp"
#include "Mountain/Rendering/RenderTarget.ixx"
#include "Mountain/Resource/Font.ixx"
#include "Mountain/Resource/Texture.ixx"
#include "Mountain/Utils/Color.ixx"
#include "Mountain/Utils/List.ixx"

#include "AnimatedCharacter.hpp"
#include "Camera.hpp"
#include "Player.hpp"

constexpr Vector2i BaseResolution = { 1280, 720 };

class GameExample : public Mountain::Game
{
public:
    Mountain::List<Mountain::Entity*> entities;
	Player* player = nullptr;
	AnimatedCharacter* character = nullptr;
	Mountain::ParticleSystem particleSystem{ 1000 };

	Mountain::RenderTarget renderTarget;
	Mountain::RenderTarget debugRenderTarget;

	Camera camera{};

	Mountain::Pointer<Mountain::Font> font;

    explicit GameExample(const char_t* windowTitle);

	// Inherited from Game
	void LoadResources() override;
	void Initialize() override;
    void Shutdown() override;
	void Update() override;
	void Render() override;
};
