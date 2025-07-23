#include "Mountain/PrecompiledHeader.hpp"

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
        Graphics::SynchronizeGpuData(Graphics::GpuDataSynchronizationFlags::ShaderImageAccess);
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

void GaussianBlur::Apply(const Vector2i textureSize, const bool_t synchronizeImageData) const
{
    Effect::Apply(textureSize, synchronizeImageData);

    BindImage(imageBindings[1].textureId, 0, Graphics::ImageShaderAccess::ReadWrite);
    BindImage(imageBindings[0].textureId, 1, Graphics::ImageShaderAccess::ReadWrite);

    Graphics::MemoryBarrier(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier);

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void GaussianBlur::SetIntensity(const int32_t newIntensity)
{
    m_Radius = newIntensity * 3;
    m_ComputeShader->SetUniform("radius", m_Radius);
    m_OtherComputeShader->SetUniform("radius", m_Radius);

    const List<float_t> kernel = ComputeKernel(newIntensity);

    BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 2, m_KernelBuffer);
    m_KernelBuffer.SetData(static_cast<int64_t>(kernel.GetSize() * sizeof(float_t)), kernel.GetData(), Graphics::BufferUsage::DynamicCopy);
}

List<float_t> GaussianBlur::ComputeKernel(const int32_t sigma) const
{
    const int32_t radius = m_Radius;
    const size_t size = radius + 1;

    List<float_t> kernel;
    kernel.Resize(size);

    float_t k = 0.f;

    const float_t inverseTwoSigmaSquare = 1.f / static_cast<float_t>(2 * sigma * sigma);

    for (int32_t i = 0; i <= radius; i++)
    {
        const float_t fi = static_cast<float_t>(i);
        const float_t value = std::exp(-fi * fi * inverseTwoSigmaSquare);
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

    kernel.ForEach([k](float_t& f) { f /= k;});

    return kernel;
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

    Graphics::MemoryBarrier(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier);

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void BoxBlur::SetRadius(const int32_t newRadius) const
{
    m_ComputeShader->SetUniform("radius", newRadius);
    m_OtherComputeShader->SetUniform("radius", newRadius);
}

void Mosaic::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/mosaic.comp");
    SetBoxSize(1);
}

void Mosaic::SetBoxSize(const int32_t newSize) const { m_ComputeShader->SetUniform("blockSize", newSize); }

void Greyscale::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/greyscale.comp");
    SetIntensity(1.f);
}

void Greyscale::SetIntensity(const float_t newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }

void Negative::LoadResources()
{
    m_ComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "effects/negative.comp");
    SetIntensity(0.5f);
}

void Negative::SetIntensity(const float_t newIntensity) const { m_ComputeShader->SetUniform("intensity", newIntensity); }
