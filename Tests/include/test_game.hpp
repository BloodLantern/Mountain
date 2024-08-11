#pragma once

#include "Mountain/game.hpp"
#include "Mountain/collision/grid.hpp"
#include "Mountain/rendering/render_target.hpp"
#include "Mountain/resource/texture.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/list.hpp"

#include "camera.hpp"
#include "player.hpp"

constexpr Vector2i BaseResolution = { 320, 180 };

class GameExample : public Mountain::Game
{
public:
    Mountain::List<Mountain::Entity*> entities;
	Player* player = nullptr;
	
	int32_t ballCount = 0;
	float_t ballTimer = 0;
	Mountain::ColorHsva lastBallColor = Mountain::ColorHsva::Red();

	Mountain::RenderTarget renderTarget;

	Camera camera{};

	Mountain::Pointer<Mountain::Font> font;

    explicit GameExample(const char_t* windowTitle);

private:
	// Inherited from Game
	void Initialize() override;
	void LoadResources() override;
	void Shutdown() override;
	void Update() override;
	void Render() override;
};
