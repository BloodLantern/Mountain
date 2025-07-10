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

    m_Radius = 1.f * 3.f;
    m_ComputeShader->SetUniform("radius", static_cast<int32_t>(Calc::Round(m_Radius)));
    m_OtherComputeShader->SetUniform("radius", static_cast<int32_t>(Calc::Round(m_Radius)));

    BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 2, m_KernelBuffer);
    const List<float_t> kernel = ComputeKernel(1.f);
    m_KernelBuffer.SetData(kernel.GetSize(), kernel.GetData(), Graphics::BufferUsage::DynamicCopy);

}

void GaussianBlur::Apply(const Vector2i textureSize, const bool_t synchronizeImageData) const
{
    Effect::Apply(textureSize, synchronizeImageData);

    BindImage(imageBindings[1].textureId, 0, Graphics::ImageShaderAccess::ReadWrite);
    BindImage(imageBindings[0].textureId, 1, Graphics::ImageShaderAccess::ReadWrite);

    Graphics::MemoryBarrier(Utils::ToFlags(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier));

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void GaussianBlur::SetIntensity(const float_t newIntensity)
{
    m_Radius = newIntensity * 3.f;
    m_ComputeShader->SetUniform("radius", static_cast<int32_t>(Calc::Round(m_Radius)));
    m_OtherComputeShader->SetUniform("radius", static_cast<int32_t>(Calc::Round(m_Radius)));
    const List<float_t> kernel = ComputeKernel(newIntensity);

    BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 2, m_KernelBuffer);
    m_KernelBuffer.SetData(kernel.GetSize() * sizeof(float_t), kernel.GetData(), Graphics::BufferUsage::DynamicCopy);
}

List<float_t> GaussianBlur::ComputeKernel(const float_t sigma) const
{
    const int32_t radius = static_cast<int32_t>(Calc::Round(m_Radius));
    const size_t size = 2 * radius + 1;
    List<float_t> kernel;
    kernel.Resize(size);

    float_t k = 0.f;

    const float_t inverseTwoSigmaSquare = 1.f / (2.f * sigma * sigma);

    for (int32_t i = -radius; i <= radius; i++)
    {
        const float_t value = std::exp(-i * i * inverseTwoSigmaSquare);
        kernel[i + radius] = value;
        k += value;
    }

    kernel.ForEach([k](float_t& f) { f /= k; });

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

    Graphics::MemoryBarrier(Utils::ToFlags(Graphics::MemoryBarrierFlags::ShaderImageAccessBarrier));

    m_OtherComputeShader->Dispatch(textureSize.x, textureSize.y);
}

void BoxBlur::SetRadius(const int32_t newRadius) const
{
    m_ComputeShader->SetUniform("radius", newRadius);
    m_OtherComputeShader->SetUniform("radius", newRadius);
}
