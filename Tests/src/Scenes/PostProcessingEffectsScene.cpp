#include "Common.hpp"

#include "Scenes/PostProcessingEffectsScene.hpp"

#include <Mountain/Rendering/Draw.hpp>
#include <Mountain/Rendering/Renderer.hpp>
#include <Mountain/Resource/ResourceManager.hpp>
#include <Mountain/Utils/ImGuiUtils.hpp>

PostProcessingEffectsScene::PostProcessingEffectsScene()
    : Base{"Post Processing Effects"}
{
}

void PostProcessingEffectsScene::LoadPersistentResources()
{
    TestScene::LoadPersistentResources();

    m_Vignette.effect.LoadResources();
    m_FilmGrain.effect.LoadResources();
    m_ChromaticAberrationAxial.effect.LoadResources();
    m_ChromaticAberrationTransverse.effect.LoadResources();
    m_BoxBlur.effect.LoadResources();
    m_GaussianBlur.effect.LoadResources();
    m_Mosaic.effect.LoadResources();
    m_Greyscale.effect.LoadResources();
}

void PostProcessingEffectsScene::LoadResources()
{
    m_LandscapeTexture = ResourceManager::Load<Texture>(FileManager::Load("assets/landscape.jpg"));
}

void PostProcessingEffectsScene::Begin()
{
    TestScene::Begin();

    const RenderTarget& renderTarget = Renderer::GetCurrentRenderTarget();
    const uint32_t renderTargetId = renderTarget.GetTextureId();

    m_IntermediateTexture.Create();
    m_IntermediateTexture.SetStorage(Graphics::InternalFormat::RedGreenBlueAlpha32Float, renderTarget.GetSize());

    m_Vignette.effect.imageBindings.Emplace(renderTargetId, 0u, Graphics::ImageShaderAccess::WriteOnly);
    m_FilmGrain.effect.imageBindings.Emplace(renderTargetId, 0u, Graphics::ImageShaderAccess::WriteOnly);

    m_ChromaticAberrationAxial.effect.imageBindings.Emplace(renderTargetId, 1u, Graphics::ImageShaderAccess::WriteOnly);
    m_ChromaticAberrationTransverse.effect.imageBindings.Emplace(renderTargetId, 1u, Graphics::ImageShaderAccess::WriteOnly);

    m_BoxBlur.effect.imageBindings.Emplace(renderTargetId, 0u, Graphics::ImageShaderAccess::ReadWrite);
    m_GaussianBlur.effect.imageBindings.Emplace(renderTargetId, 0u, Graphics::ImageShaderAccess::ReadWrite);

    m_Mosaic.effect.imageBindings.Emplace(renderTargetId, 1u, Graphics::ImageShaderAccess::WriteOnly);
    m_Greyscale.effect.imageBindings.Emplace(renderTargetId, 0u, Graphics::ImageShaderAccess::WriteOnly);

    const uint32_t intermediateTextureId = m_IntermediateTexture.GetId();

    m_ChromaticAberrationAxial.effect.imageBindings.Emplace(intermediateTextureId, 0u, Graphics::ImageShaderAccess::ReadOnly);
    m_ChromaticAberrationTransverse.effect.imageBindings.Emplace(intermediateTextureId, 0u, Graphics::ImageShaderAccess::ReadOnly);

    m_BoxBlur.effect.imageBindings.Emplace(intermediateTextureId, 1u, Graphics::ImageShaderAccess::ReadWrite);
    m_GaussianBlur.effect.imageBindings.Emplace(intermediateTextureId, 1u, Graphics::ImageShaderAccess::ReadWrite);

    m_Mosaic.effect.imageBindings.Emplace(intermediateTextureId, 0u, Graphics::ImageShaderAccess::ReadOnly);

}

void PostProcessingEffectsScene::Render()
{
    TestScene::Render();

    const RenderTarget& renderTarget = Renderer::GetCurrentRenderTarget();
    const Vector2i renderTargetSize = renderTarget.GetSize();

    Draw::Texture(*m_LandscapeTexture, Vector2::Zero(), renderTargetSize / static_cast<Vector2>(m_LandscapeTexture->GetSize()));
    Draw::Flush();

    ApplyEffectIfEnabled(m_Vignette);
    ApplyEffectIfEnabled(m_FilmGrain);
    ApplyEffectIfEnabled(m_ChromaticAberrationAxial);
    ApplyEffectIfEnabled(m_ChromaticAberrationTransverse);
    ApplyEffectIfEnabled(m_BoxBlur);
    ApplyEffectIfEnabled(m_GaussianBlur);
    ApplyEffectIfEnabled(m_Mosaic);
    ApplyEffectIfEnabled(m_Greyscale);
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
    ShowEffectImGui("Box Blur", m_BoxBlur, [](auto& e)
    {
        static int32_t radius = 1;
        ImGui::DragInt("radius", &radius, 0.1f, 0, 10);
        e.SetRadius(radius);
    });
    ShowEffectImGui("Gaussian Blur ", m_GaussianBlur, [](auto& e)
    {
        static float_t intensity = 1.f;
        ImGui::DragFloat("intensity", &intensity, 0.01f, 0.f, 10.f);
        e.SetIntensity(intensity);
    });
    ShowEffectImGui("Mosaic ", m_Mosaic, [](auto& e)
    {
        static int32_t size = 1;
        ImGui::DragInt("intensity", &size, 0.1f, 1, 150);
        e.SetBoxSize(size);
    });
    ShowEffectImGui("Greyscale", m_Greyscale);
}

void PostProcessingEffectsScene::End()
{
    m_Vignette.effect.imageBindings.Clear();
    m_FilmGrain.effect.imageBindings.Clear();
    m_ChromaticAberrationAxial.effect.imageBindings.Clear();
    m_ChromaticAberrationTransverse.effect.imageBindings.Clear();
    m_BoxBlur.effect.imageBindings.Clear();
    m_GaussianBlur.effect.imageBindings.Clear();
    m_Mosaic.effect.imageBindings.Clear();
    m_Greyscale.effect.imageBindings.Clear();

    m_IntermediateTexture.Delete();

    TestScene::End();
}

void PostProcessingEffectsScene::UnloadResources()
{
    const Pointer<File> file = m_LandscapeTexture->GetFile();
    ResourceManager::Unload(m_LandscapeTexture);
    FileManager::Unload(file);
}

void PostProcessingEffectsScene::UpdateIntermediateTexture() const
{
    const RenderTarget& renderTarget = Renderer::GetCurrentRenderTarget();

    Graphics::CopyTextureData(
        renderTarget.GetTextureId(),
        0,
        Vector2i::Zero(),
        m_IntermediateTexture.GetId(),
        0,
        Vector2i::Zero(),
        renderTarget.GetSize()
    );
}
