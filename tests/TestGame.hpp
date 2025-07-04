#pragma once

#include "Mountain/Game.hpp"
#include "Mountain/Collision/Grid.hpp"
#include "Mountain/Rendering/ParticleSystem.hpp"
#include "Mountain/Rendering/RenderTarget.hpp"
#include "Mountain/Resource/Font.hpp"
#include "Mountain/Resource/Texture.hpp"
#include "Mountain/Utils/Color.hpp"
#include "Mountain/Utils/List.hpp"

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
