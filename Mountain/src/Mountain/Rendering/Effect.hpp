#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Rendering/RenderTarget.hpp"
#include "Mountain/Resource/ComputeShader.hpp"
#include "Mountain/Resource/Texture.hpp"

namespace Mountain
{
    class Effect
    {
    public:
        struct MOUNTAIN_API ImageBinding
        {
            uint32_t textureId;
            uint32_t shaderBinding;
            Graphics::ImageShaderAccess shaderAccess;
        };

        List<ImageBinding> imageBindings;

        MOUNTAIN_API Effect() = default;
        MOUNTAIN_API virtual ~Effect() = default;

        DEFAULT_COPY_MOVE_OPERATIONS(Effect)

        MOUNTAIN_API virtual void LoadResources() = 0;

        /// @brief Applies this effect to the bound images.
        ///
        /// @param textureSize The texture size to give to the compute shader. The shader will be called once for each pixel of the given size.
        /// @param synchronizeImageData Whether to synchronize the CPU image data with the modified GPU one.
        /// This effectively means that the CPU will wait for the compute shader to finish executing before returning from this function.
        /// If this is @c false, and you want to access the modified GPU image, you need to manually synchronize the GPU data afterward using
        /// @c Graphics::SynchronizeGpuData() with @c GpuDataSynchronizationFlags::ShaderImageAccess.
        MOUNTAIN_API virtual void Apply(Vector2i textureSize, bool_t synchronizeImageData) const;

    protected:
        Pointer<ComputeShader> m_ComputeShader;
    };

    class Vignette : public Effect
    {
    public:
        MOUNTAIN_API void LoadResources() override;

        MOUNTAIN_API void SetStrength(float_t newStrength) const;
    };

    class FilmGrain : public Effect
    {
    public:
        MOUNTAIN_API void LoadResources() override;

        MOUNTAIN_API void SetIntensity(float_t newIntensity) const;
    };

    class ChromaticAberrationAxial : public Effect
    {
    public:
        MOUNTAIN_API void LoadResources() override;

        MOUNTAIN_API void SetIntensity(float_t newIntensity) const;

        MOUNTAIN_API void SetAngle(float_t newAngle) const;
    };

    class ChromaticAberrationTransverse : public Effect
    {
    public:
        MOUNTAIN_API void LoadResources() override;

        MOUNTAIN_API void SetIntensity(float_t newIntensity) const;
    };

    // Effect will be applied on the first texture and the second one is used as a buffer
    class GaussianBlurLow : public Effect
    {
    public:
        MOUNTAIN_API void LoadResources() override;

        MOUNTAIN_API void Apply(Vector2i textureSize, bool_t synchronizeImageData) const override;

    protected:
        Pointer<ComputeShader> m_OtherComputeShader;

    };

    // Effect will be applied on the first texture and the second one is used as a buffer
    class GaussianBlurHigh : public Effect
    {
    public:
        MOUNTAIN_API void LoadResources() override;

        MOUNTAIN_API void Apply(Vector2i textureSize, bool_t synchronizeImageData) const override;

    protected:
        Pointer<ComputeShader> m_OtherComputeShader;

    };

    // Effect will be applied on the first texture and the second one is used as a buffer
    class BoxBlur : public Effect
    {
    public:
        MOUNTAIN_API void LoadResources() override;

        MOUNTAIN_API void Apply(Vector2i textureSize, bool_t synchronizeImageData) const override;

        MOUNTAIN_API void SetRadius(int32_t newRadius) const;


    protected:
        Pointer<ComputeShader> m_OtherComputeShader;

    };
}
