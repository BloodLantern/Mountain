#pragma once

#include "Mountain/core.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/utils.hpp"

namespace Mountain::ParticleSystemModules
{
    enum class MOUNTAIN_API Types : uint32_t // We might as well use an uint as it is the minimum amount of data we can transfer to the shader
    {
        None = 0,

        Shape               = 1 << 0,
        ForceOverLifetime   = 1 << 1,
        ColorOverLifetime   = 1 << 2,
        ColorBySpeed        = 1 << 3,
        Noise               = 1 << 4,
        Collision           = 1 << 5,
        Lights              = 1 << 6,
        Trails              = 1 << 7,

        Default = Shape,

        All = 0xFFFFFFFF
    };

    class MOUNTAIN_API Base
    {
    public:
        Base() = default;
        virtual ~Base() = default;
        DEFAULT_COPY_MOVE_OPERATIONS(Base)

        virtual void SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const = 0;
        virtual void RenderImGui(uint32_t* enabledModulesInt) = 0;

    protected:
        bool_t BeginImGui(uint32_t* enabledModulesInt, Types type, const char_t* name) const;
        void EndImGui() const;
    };

    class MOUNTAIN_API Shape : public Base
    {
    public:
        void SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const override;
        void RenderImGui(uint32_t* enabledModulesInt) override;
    };

    class MOUNTAIN_API ColorOverLifetime : public Base
    {
    public:
        Color target = Color::Transparent();

        void SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const override;
        void RenderImGui(uint32_t* enabledModulesInt) override;
    };

    class MOUNTAIN_API ForceOverLifetime : public Base
    {
    public:
        Vector2 force;

        void SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const override;
        void RenderImGui(uint32_t* enabledModulesInt) override;
    };
}

ENUM_FLAGS(Mountain::ParticleSystemModules::Types)
