

#include "Mountain/Graphics/Effect.hpp"

#include "Mountain/Graphics/Draw.hpp"
#include "Mountain/Graphics/Renderer.hpp"
#include "Mountain/Resource/ComputeShader.hpp"
#include "Mountain/Resource/ResourceManager.hpp"

using namespace Mountain;

void Effect::Apply(const Vector2i textureSize, const bool synchronizeImageData) const
{
    u32 currentRenderTargetId = Renderer::GetCurrentRenderTarget().GetTextureId();

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
        Graphics::SynchronizeGpuData(Graphics::GpuDataSynchronizationFlags::ShaderImageAccess);
}

void Vignette::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/vignette.comp");
    SetStrength(1.f);
}

void Vignette::SetStrength(const f32 newStrength) const { m_ComputeShader->SetUniform("strength", newStrength); }

void FilmGrain::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/film_grain.comp");
    SetIntensity(1.f);
}

void FilmGrain::SetIntensity(const f32 newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }

void ChromaticAberrationAxial::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/chromatic_aberration_axial.comp");
    SetIntensity(1.f);
}

void ChromaticAberrationAxial::SetIntensity(const f32 newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }

void ChromaticAberrationAxial::SetAngle(const f32 newAngle) const { m_ComputeShader->SetUniform("angle", newAngle); }

void ChromaticAberrationTransverse::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/chromatic_aberration_transverse.comp");
    SetIntensity(1.f);
}

void ChromaticAberrationTransverse::SetIntensity(const f32 newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }

GaussianBlur::GaussianBlur()
{
    m_KernelBuffer.Create();
    m_KernelBuffer.SetDebugName("Kernel buffer SSBO");
}

GaussianBlur::~GaussianBlur()
{
    m_KernelBuffer.Delete();
}

void GaussianBlur::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/gaussian_blur_horizontal.comp");
    m_OtherComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/gaussian_blur_vertical.comp");

    SetIntensity(1);
}

void GaussianBlur::Apply(const Vector2i textureSize, const bool synchronizeImageData) const
{
    Effect::Apply(textureSize, synchronizeImageData);

    BindImage(imageBindings[1].textureId, 0, Graphics::ImageShaderAccess::ReadWrite);
    BindImage(imageBindings[0].textureId, 1, Graphics::ImageShaderAccess::ReadWrite);

    Graphics::MemoryBarrier(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier);

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void GaussianBlur::SetIntensity(const s32 newIntensity)
{
    m_Radius = newIntensity * 3;
    m_ComputeShader->SetUniform("radius", m_Radius);
    m_OtherComputeShader->SetUniform("radius", m_Radius);

    const List<f32> kernel = ComputeKernel(newIntensity);

    BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 2, m_KernelBuffer);
    m_KernelBuffer.SetData(static_cast<s64>(kernel.GetSize() * sizeof(f32)), kernel.GetData(), Graphics::BufferUsage::DynamicCopy);
}

List<f32> GaussianBlur::ComputeKernel(const s32 sigma) const
{
    const s32 radius = m_Radius;
    const usize size = radius + 1;

    List<f32> kernel;
    kernel.Resize(size);

    f32 k = 0.f;

    const f32 inverseTwoSigmaSquare = 1.f / static_cast<f32>(2 * sigma * sigma);

    for (s32 i = 0; i <= radius; i++)
    {
        const f32 fi = static_cast<f32>(i);
        const f32 value = std::exp(-fi * fi * inverseTwoSigmaSquare);
        kernel[i] = value;

        if (i == 0)
        {
            k += value;
        }
        else
        {
            k += 2.f * value;
        }
    }

    kernel.ForEach([k](f32& f) { f /= k;});

    return kernel;
}

void BoxBlur::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/box_blur_horizontal.comp");
    m_OtherComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/box_blur_vertical.comp");
    m_ComputeShader->SetUniform("radius", 1);
    m_OtherComputeShader->SetUniform("radius", 1);
}

void BoxBlur::Apply(const Vector2i textureSize, const bool synchronizeImageData) const
{
    Effect::Apply(textureSize, synchronizeImageData);

    BindImage(imageBindings[1].textureId, 0, Graphics::ImageShaderAccess::ReadWrite);
    BindImage(imageBindings[0].textureId, 1, Graphics::ImageShaderAccess::ReadWrite);

    Graphics::MemoryBarrier(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier);

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void BoxBlur::SetRadius(const s32 newRadius) const
{
    m_ComputeShader->SetUniform("radius", newRadius);
    m_OtherComputeShader->SetUniform("radius", newRadius);
}

void Mosaic::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/mosaic.comp");
    SetBoxSize(1);
}

void Mosaic::SetBoxSize(const s32 newSize) const { m_ComputeShader->SetUniform("blockSize", newSize); }

void Grayscale::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/grayscale.comp");
    SetIntensity(1.f);
}

void Grayscale::SetIntensity(const f32 newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }

void Negative::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/negative.comp");
    SetIntensity(0.5f);
}

void Negative::SetIntensity(const f32 newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }
