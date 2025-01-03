﻿#pragma once

#include "Mountain/core.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/utils.hpp"

namespace Mountain::ParticleSystemModules
{
    enum class MOUNTAIN_API Types : uint32_t // We might as well use an uint as it is the minimum amount of data we can transfer to the shader
    {
        None = 0,

        Emission            = 1 << 0,
        Shape               = 1 << 1,
        ForceOverLifetime   = 1 << 2,
        ColorOverLifetime   = 1 << 3,
        ColorBySpeed        = 1 << 4,
        Noise               = 1 << 5,
        Collision           = 1 << 6,
        Lights              = 1 << 7,
        Trails              = 1 << 8,

        All = 0xFFFFFFFF
    };

    struct MOUNTAIN_API Base
    {
        Base() = default;
        virtual ~Base() = default;
        DEFAULT_COPY_MOVE_OPERATIONS(Base)

        virtual void SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const = 0;
        virtual void RenderImGui(uint32_t* enabledModulesInt) = 0;

    protected:
        bool_t BeginImGui(uint32_t* enabledModulesInt, Types type, const char_t* name) const;
        void EndImGui() const;
    };

    struct MOUNTAIN_API ColorOverLifetime : Base
    {
        Color target = Color::Transparent();

        void SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const override;
        void RenderImGui(uint32_t* enabledModulesInt) override;
    };

    struct MOUNTAIN_API ForceOverLifetime : Base
    {
        Vector2 force;

        void SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const override;
        void RenderImGui(uint32_t* enabledModulesInt) override;
    };
}

ENUM_FLAGS(Mountain::ParticleSystemModules::Types)
