#include "Mountain/rendering/effect.hpp"

#include "Mountain/rendering/draw.hpp"
#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/compute_shader.hpp"
#include "Mountain/resource/resource_manager.hpp"

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
        SynchronizeGpuData(Graphics::GpuDataSynchronizationType::ShaderImageAccess);
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
