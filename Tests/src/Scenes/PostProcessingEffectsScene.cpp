#include "Scenes/PostProcessingEffectsScene.hpp"

#include <Mountain/Rendering/Draw.hpp>
#include <Mountain/Rendering/Renderer.hpp>
#include <Mountain/Resource/ResourceManager.hpp>

PostProcessingEffectsScene::PostProcessingEffectsScene()
    : Base{"Post Processing Effects"}
{
}

void PostProcessingEffectsScene::Begin()
{
    TestScene::Begin();

    uint32_t renderTargetTextureId = Mountain::Renderer::GetCurrentRenderTarget().GetTextureId();

    m_Vignette.effect.imageBindings.Emplace(renderTargetTextureId, 0u, Mountain::Graphics::ImageShaderAccess::WriteOnly);
    m_FilmGrain.effect.imageBindings.Emplace(renderTargetTextureId, 0u, Mountain::Graphics::ImageShaderAccess::WriteOnly);
}

void PostProcessingEffectsScene::Render()
{
    TestScene::Render();

    const Vector2i renderTargetSize = Mountain::Renderer::GetCurrentRenderTarget().GetSize();

    Mountain::Draw::Texture(*m_LandscapeTexture, Vector2::Zero(), renderTargetSize / static_cast<Vector2>(m_LandscapeTexture->GetSize()));
    Mountain::Draw::Flush();

    if (m_Vignette.enabled)
        m_Vignette.effect.Apply(renderTargetSize, false);
    if (m_FilmGrain.enabled)
        m_FilmGrain.effect.Apply(renderTargetSize, false);
}

void PostProcessingEffectsScene::RenderImGui()
{
    TestScene::RenderImGui();

    ShowEffectImGui("Vignette", m_Vignette, [](auto& e)
    {
        static float_t strength = 1.f;
        ImGui::DragFloat("strength", &strength, 0.01f, 0.f, 10.f);
        e.SetStrength(strength);
    });
    ShowEffectImGui("Film Grain", m_FilmGrain, [](auto& e)
    {
        static float_t intensity = 1.f;
        ImGui::DragFloat("intensity", &intensity, 0.01f, 0.f, 10.f);
        e.SetIntensity(intensity);
    });
}

void PostProcessingEffectsScene::End()
{
    m_Vignette.effect.imageBindings.Clear();
    m_FilmGrain.effect.imageBindings.Clear();

    TestScene::End();
}

void PostProcessingEffectsScene::LoadPersistentResources()
{
    TestScene::LoadPersistentResources();

    m_Vignette.effect.LoadResources();
    m_FilmGrain.effect.LoadResources();
}

void PostProcessingEffectsScene::LoadResources()
{
    m_LandscapeTexture = Mountain::ResourceManager::Load<Mountain::Texture>(Mountain::FileManager::Load("assets/landscape.jpg"));
}

void PostProcessingEffectsScene::UnloadResources()
{
    Mountain::ResourceManager::Unload(m_LandscapeTexture);
    Mountain::FileManager::Unload(m_LandscapeTexture->GetFile()->GetPath());
}
