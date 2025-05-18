#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Resource/ComputeShader.hpp"
#include "Mountain/Utils/Color.hpp"
#include "Mountain/Utils/Utils.ixx"

namespace Mountain
{
    class ParticleSystem;
}

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
        virtual void RenderDebug(const ParticleSystem& system, Vector2 renderTargetSizeDiff) const;

    protected:
        bool_t BeginImGui(uint32_t* enabledModulesInt, Types type) const;
        void EndImGui() const;
    };

    enum class ShapeType : uint32_t  // NOLINT(performance-enum-size)
    {
        Circle,
        Line,
        Rectangle,
    };

    enum class ShapeArcMode : uint32_t  // NOLINT(performance-enum-size)
    {
        Random,
        Loop,
        PingPong,
        BurstSpread,
    };

    struct ShapeArc
    {
        ShapeArcMode mode = ShapeArcMode::Random;
        float_t spread = 0.f;
    };

    struct ShapeCircle
    {
        float_t radius = 1.f;
        /// @brief A value of 0 means the particles can only spawn on the edge of the radius, while 1 means they can spawn everywhere within the given radius
        float_t radiusThickness = 1.f;
        /// @brief Angle in radians in the range [0, 2pi]
        float_t arcAngle = Calc::TwoPi;
        ShapeArc arc;
    };

    struct ShapeLine
    {
        float_t radius = 1.f;
        ShapeArc arc;
    };

    struct ShapeRectangle
    {
        /// @see ShapeCircle::radiusThickness
        Vector2 scaleThickness = Vector2::One();
    };

    class Shape : public Base
    {
    public:
        ShapeType type = ShapeType::Circle;

        ShapeCircle circle;
        ShapeLine line;
        ShapeRectangle rectangle;

        Vector2 offset;
        float_t rotation;
        Vector2 scale = Vector2::One();

        float_t randomizeDirection = 0.f;
        float_t randomizeRotation = 0.f;
        float_t randomizePosition = 0.f;

        bool_t showSpawnArea = false;

        MOUNTAIN_API void SetComputeShaderUniforms(const ComputeShader& computeShader, Types enabledModules) const override;
        MOUNTAIN_API void RenderImGui(uint32_t* enabledModulesInt) override;
        MOUNTAIN_API void RenderDebug(const ParticleSystem& system, Vector2 renderTargetSizeDiff) const override;
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
