#pragma once

#include <Mountain/Rendering/Effect.hpp>

#include "Scenes/TestScene.hpp"

template <Mountain::Concepts::Effect T>
struct PostProcessingEffect
{
	bool_t enabled;
	T effect;
};

class PostProcessingEffectsScene : public TestScene
{
public:
	using Base = TestScene;

	PostProcessingEffectsScene();

	void Begin() override;

	void Render() override;

	void RenderImGui() override;

	void End() override;

	// We're only getting the effect shaders. No load occurs here, so we don't need to unload afterward
	void LoadPersistentResources() override;

	void LoadResources() override;

	void UnloadResources() override;

private:
	Mountain::Pointer<Mountain::Texture> m_LandscapeTexture;

	PostProcessingEffect<Mountain::Vignette> m_Vignette{};
	PostProcessingEffect<Mountain::FilmGrain> m_FilmGrain{};

	template <Mountain::Concepts::Effect T>
	void ShowEffectImGui(
		const std::string& name,
		PostProcessingEffect<T>& effect,
		const std::type_identity_t<std::function<void(T& effect)>>& additionalAction = std::identity{}
	);
};

// Start of PostProcessingEffectsScene.inl

template <Mountain::Concepts::Effect T>
void PostProcessingEffectsScene::ShowEffectImGui(
	const std::string& name,
	PostProcessingEffect<T>& effect,
	const std::type_identity_t<std::function<void(T& effect)>>& additionalAction
)
{
	const static std::string CheckboxLabel = "##" + name + "Enabled";
	ImGui::Checkbox(CheckboxLabel.c_str(), &effect.enabled);
	ImGui::SameLine();
	if (ImGui::TreeNode(name.c_str()))
	{
		additionalAction(effect.effect);
		ImGui::TreePop();
	}
}
