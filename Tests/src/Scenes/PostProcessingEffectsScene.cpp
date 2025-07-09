#include "Scenes/PostProcessingEffectsScene.hpp"

#include <Mountain/Rendering/Draw.hpp>
#include <Mountain/Rendering/Renderer.hpp>
#include <Mountain/Resource/ResourceManager.hpp>
#include <Mountain/Utils/ImGuiUtils.hpp>

PostProcessingEffectsScene::PostProcessingEffectsScene()
    : Base{"Post Processing Effects"}
{
}

void PostProcessingEffectsScene::Begin()
{
    TestScene::Begin();

    const Mountain::RenderTarget& renderTarget = Mountain::Renderer::GetCurrentRenderTarget();
    const uint32_t renderTargetId = renderTarget.GetTextureId();

    m_IntermediateTexture.Create();
    m_IntermediateTexture.SetStorage(Mountain::Graphics::InternalFormat::RedGreenBlueAlpha32Float, renderTarget.GetSize());

    m_Vignette.effect.imageBindings.Emplace(renderTargetId, 0u, Mountain::Graphics::ImageShaderAccess::WriteOnly);
    m_FilmGrain.effect.imageBindings.Emplace(renderTargetId, 0u, Mountain::Graphics::ImageShaderAccess::WriteOnly);
    m_ChromaticAberrationAxial.effect.imageBindings.Emplace(renderTargetId, 1u, Mountain::Graphics::ImageShaderAccess::WriteOnly);
    m_ChromaticAberrationTransverse.effect.imageBindings.Emplace(renderTargetId, 1u, Mountain::Graphics::ImageShaderAccess::WriteOnly);

    const uint32_t intermediateTextureId = m_IntermediateTexture.GetId();

    m_ChromaticAberrationAxial.effect.imageBindings.Emplace(intermediateTextureId, 0u, Mountain::Graphics::ImageShaderAccess::ReadOnly);
    m_ChromaticAberrationTransverse.effect.imageBindings.Emplace(intermediateTextureId, 0u, Mountain::Graphics::ImageShaderAccess::ReadOnly);
}

void PostProcessingEffectsScene::Render()
{
    TestScene::Render();

    const Mountain::RenderTarget& renderTarget = Mountain::Renderer::GetCurrentRenderTarget();
    const Vector2i renderTargetSize = renderTarget.GetSize();

    Mountain::Draw::Texture(*m_LandscapeTexture, Vector2::Zero(), renderTargetSize / static_cast<Vector2>(m_LandscapeTexture->GetSize()));
    Mountain::Draw::Flush();

    ApplyEffectIfEnabled(m_Vignette);
    ApplyEffectIfEnabled(m_FilmGrain);
    ApplyEffectIfEnabled(m_ChromaticAberrationAxial);
    ApplyEffectIfEnabled(m_ChromaticAberrationTransverse);
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
    ShowEffectImGui("Chromatic Aberration Axial", m_ChromaticAberrationAxial, [](auto& e)
    {
        static float_t intensity = 1.f;
        ImGui::DragFloat("intensity", &intensity, 0.01f, 0.f, 10.f);
        static float angle = 0;
        ImGui::DragAngle("angle", &angle);
        e.SetIntensity(intensity);
        e.SetAngle(angle);
    });
    ShowEffectImGui("Chromatic Aberration Transverse", m_ChromaticAberrationTransverse, [](auto& e)
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
    m_ChromaticAberrationAxial.effect.imageBindings.Clear();
    m_ChromaticAberrationTransverse.effect.imageBindings.Clear();

    m_IntermediateTexture.Delete();

    TestScene::End();
}

void PostProcessingEffectsScene::LoadPersistentResources()
{
    TestScene::LoadPersistentResources();

    m_Vignette.effect.LoadResources();
    m_FilmGrain.effect.LoadResources();
    m_ChromaticAberrationAxial.effect.LoadResources();
    m_ChromaticAberrationTransverse.effect.LoadResources();
}

void PostProcessingEffectsScene::LoadResources()
{
    m_LandscapeTexture = Mountain::ResourceManager::Load<Mountain::Texture>(Mountain::FileManager::Load("assets/landscape.jpg"));
}

void PostProcessingEffectsScene::UnloadResources()
{
    Mountain::Pointer<Mountain::File> file = m_LandscapeTexture->GetFile();
    Mountain::ResourceManager::Unload(m_LandscapeTexture);
    Mountain::FileManager::Unload(file->GetPath());
}

void PostProcessingEffectsScene::UpdateIntermediateTexture() const
{
    const Mountain::RenderTarget& renderTarget = Mountain::Renderer::GetCurrentRenderTarget();

    Mountain::Graphics::CopyTextureData(
        renderTarget.GetTextureId(),
        0,
        Vector2i::Zero(),
        m_IntermediateTexture.GetId(),
        0,
        Vector2i::Zero(),
        renderTarget.GetSize()
    );
}
