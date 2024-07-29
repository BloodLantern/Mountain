#pragma once

#include "camera.hpp"
#include "game.hpp"
#include "player.hpp"
#include "collision/grid.hpp"
#include "rendering/render_target.hpp"
#include "resource/texture.hpp"
#include "utils/color.hpp"
#include "utils/list.hpp"

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
