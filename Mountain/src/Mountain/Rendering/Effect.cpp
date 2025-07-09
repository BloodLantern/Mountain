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

void ChromaticAberrationTransverse::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/chromatic_aberration_transverse.comp");
    SetIntensity(1.f);
}

void ChromaticAberrationTransverse::SetIntensity(const float_t newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }

void GaussianBlurLow::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/gaussian_blur_horizontal_low.comp");
    m_OtherComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/gaussian_blur_vertical_low.comp");
}

void GaussianBlurLow::Apply(const Vector2i textureSize, const bool_t synchronizeImageData) const
{
    Effect::Apply(textureSize, synchronizeImageData);

    BindImage(imageBindings[1].textureId, 0, Graphics::ImageShaderAccess::ReadWrite);
    BindImage(imageBindings[0].textureId, 1, Graphics::ImageShaderAccess::ReadWrite);

    Graphics::MemoryBarrier(Utils::ToFlags(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier));

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void GaussianBlurHigh::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/gaussian_blur_horizontal_high.comp");
    m_OtherComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/gaussian_blur_vertical_high.comp");
}

void GaussianBlurHigh::Apply(const Vector2i textureSize, const bool_t synchronizeImageData) const
{
    Effect::Apply(textureSize, synchronizeImageData);

    BindImage(imageBindings[1].textureId, 0, Graphics::ImageShaderAccess::ReadWrite);
    BindImage(imageBindings[0].textureId, 1, Graphics::ImageShaderAccess::ReadWrite);

    Graphics::MemoryBarrier(Utils::ToFlags(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier));

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void BoxBlur::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/box_blur_horizontal.comp");
    m_OtherComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/box_blur_vertical.comp");
    m_ComputeShader->SetUniform("radius", 1);
    m_OtherComputeShader->SetUniform("radius", 1);
}

void BoxBlur::Apply(const Vector2i textureSize, const bool_t synchronizeImageData) const
{
    Effect::Apply(textureSize, synchronizeImageData);

    BindImage(imageBindings[1].textureId, 0, Graphics::ImageShaderAccess::ReadWrite);
    BindImage(imageBindings[0].textureId, 1, Graphics::ImageShaderAccess::ReadWrite);

    Graphics::MemoryBarrier(Utils::ToFlags(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier));

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void BoxBlur::SetRadius(const int32_t newRadius) const
{
    m_ComputeShader->SetUniform("radius", newRadius);
    m_OtherComputeShader->SetUniform("radius", newRadius);

}