#pragma once

#include "Mountain/game.hpp"
#include "Mountain/collision/grid.hpp"
#include "Mountain/rendering/particle_system.hpp"
#include "Mountain/rendering/render_target.hpp"
#include "Mountain/resource/texture.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/list.hpp"

#include "animated_character.hpp"
#include "camera.hpp"
#include "player.hpp"

constexpr Vector2i BaseResolution = { 320, 180 };

class GameExample : public Mountain::Game
{
public:
    Mountain::List<Mountain::Entity*> entities;
	Player* player = nullptr;
	AnimatedCharacter* character = nullptr;
	Mountain::ParticleSystem particleSystem{ 1000 };

	Mountain::RenderTarget renderTarget;

	Camera camera{};

	Mountain::Pointer<Mountain::Font> font;

    explicit GameExample(const char_t* windowTitle);

	// Inherited from Game
	void Initialize() override;
	void LoadResources() override;
    void Shutdown() override;
	void Update() override;
	void Render() override;
};
