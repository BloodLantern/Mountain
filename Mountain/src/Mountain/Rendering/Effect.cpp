#include "Mountain/Rendering/Effect.hpp"

#include "Mountain/Rendering/Draw.hpp"
#include "Mountain/Rendering/Renderer.hpp"
#include "Mountain/Resource/ComputeShader.hpp"
#include "Mountain/Resource/ResourceManager.hpp"

using namespace Mountain;

void Effect::Apply(const Vector2i textureSize, const bool_t synchronizeImageData) const
{
    uint32_t currentRenderTargetId = Renderer::GetCurrentRenderTarget().GetTextureId();

    for (const ImageBinding& binding : imageBindings)
    {
        BindImage(binding.textureId, binding.shaderBinding, binding.shaderAccess);

        if (binding.textureId == currentRenderTargetId)
        {
            Draw::Flush();
            // Avoid flushing multiple times in case the RenderTarget texture was bound more than once
            currentRenderTargetId = 0;
        }
    }

    m_ComputeShader->Dispatch(textureSize.x, textureSize.y);

    if (synchronizeImageData)
        Graphics::SynchronizeGpuData(Utils::ToFlags(Graphics::GpuDataSynchronizationFlags::ShaderImageAccess));
}

void Vignette::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/vignette.comp");
    SetStrength(1.f);
}

void Vignette::SetStrength(const float_t newStrength) const { m_ComputeShader->SetUniform("strength", newStrength); }

void FilmGrain::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/film_grain.comp");
    SetIntensity(1.f);
}

void FilmGrain::SetIntensity(const float_t newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }

void ChromaticAberrationAxial::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/chromatic_aberration_axial.comp");
    SetIntensity(1.f);
}

void ChromaticAberrationAxial::SetIntensity(const float_t newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }

void ChromaticAberrationAxial::SetAngle(const float_t newAngle) const { m_ComputeShader->SetUniform("angle", newAngle); }
