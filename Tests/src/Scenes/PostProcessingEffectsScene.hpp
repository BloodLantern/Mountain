#pragma once

#include <Mountain/Rendering/Effect.hpp>
#include <Mountain/Rendering/Renderer.hpp>

#include "Scenes/TestScene.hpp"

template <Concepts::Effect T>
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
	Pointer<Texture> m_LandscapeTexture;

	PostProcessingEffect<Vignette> m_Vignette{};
	PostProcessingEffect<FilmGrain> m_FilmGrain{};
	PostProcessingEffect<ChromaticAberrationAxial> m_ChromaticAberrationAxial{};
	PostProcessingEffect<ChromaticAberrationTransverse> m_ChromaticAberrationTransverse{};
	PostProcessingEffect<GaussianBlur> m_GaussianBlur{};
	PostProcessingEffect<BoxBlur> m_BoxBlur{};
	PostProcessingEffect<Mosaic> m_Mosaic{};
	PostProcessingEffect<Greyscale> m_Greyscale{};

	Graphics::GpuTexture m_IntermediateTexture;

	template <Concepts::Effect T>
	static void ShowEffectImGui(const std::string& name, PostProcessingEffect<T>& effect);

	template <Concepts::Effect T>
	void ShowEffectImGui(
		const std::string& name,
		PostProcessingEffect<T>& effect,
		const Meta::Identity<std::function<void(T& effect)>>& additionalAction
	);

	template <Concepts::Effect T>
	void ApplyEffectIfEnabled(const PostProcessingEffect<T>& effect);

	void UpdateIntermediateTexture() const;
};

// Start of PostProcessingEffectsScene.inl

template <Concepts::Effect T>
void PostProcessingEffectsScene::ShowEffectImGui(const std::string& name, PostProcessingEffect<T>& effect)
{
	const std::string checkboxLabel = "##" + name + "Enabled";

	ImGui::Checkbox(checkboxLabel.c_str(), &effect.enabled);
	ImGui::SameLine();
	if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf))
		ImGui::TreePop();
}

template <Concepts::Effect T>
void PostProcessingEffectsScene::ShowEffectImGui(
	const std::string& name,
	PostProcessingEffect<T>& effect,
	const Meta::Identity<std::function<void(T& effect)>>& additionalAction
)
{
	const std::string checkboxLabel = "##" + name + "Enabled";

	ImGui::Checkbox(checkboxLabel.c_str(), &effect.enabled);
	ImGui::SameLine();
	if (ImGui::TreeNode(name.c_str()))
	{
		additionalAction(effect.effect);
		ImGui::TreePop();
	}
}

template <Concepts::Effect T>
void PostProcessingEffectsScene::ApplyEffectIfEnabled(const PostProcessingEffect<T>& effect)
{
	if (effect.enabled)
	{
		if (effect.effect.imageBindings.Contains([&](const auto& binding) { return binding.textureId == m_IntermediateTexture.GetId(); }))
			UpdateIntermediateTexture();

		effect.effect.Apply(Renderer::GetCurrentRenderTarget().GetSize(), false);
	}
}
