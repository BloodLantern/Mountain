#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Resource/ComputeShader.hpp"
#include "Mountain/Resource/Shader.hpp"
#include "Mountain/Resource/Texture.hpp"
#include "Mountain/Utils/Color.hpp"
#include "Mountain/Utils/Utils.hpp"

#define PARTICLE_SYSTEM_MODULE_CONSTRUCTOR(type) type() : ::Mountain::ParticleSystemModules::ModuleBase(::Mountain::ParticleSystemModules::Types::type) {}

namespace Mountain
{
    class ParticleSystem;
}

namespace Mountain::ParticleSystemModules
{
    enum class MOUNTAIN_API Types : uint32_t
    {
        None = 0,

        Shape                       = 1 << 0,
        VelocityOverLifetime        = 1 << 1,
        LimitVelocityOverLifetime   = 1 << 2,
        InheritVelocity             = 1 << 3,
        LifetimeByEmitterSpeed      = 1 << 4,
        ForceOverLifetime           = 1 << 5,
        ColorOverLifetime           = 1 << 6,
        ColorBySpeed                = 1 << 7,
        SizeOverLifetime            = 1 << 8,
        SizeBySpeed                 = 1 << 9,
        RotationOverLifetime        = 1 << 10,
        RotationBySpeed             = 1 << 11,
        Noise                       = 1 << 12,
        Collision                   = 1 << 13,
        SubEmitters                 = 1 << 14,
        TextureSheetAnimation       = 1 << 15,
        Lights                      = 1 << 16,
        Trails                      = 1 << 17,
        Renderer                    = 1 << 18,

        Default = Shape | Renderer,

        All = 0xFFFFFFFF
    };

    class MOUNTAIN_API ModuleBase
    {
    public:
        explicit ModuleBase(Types type);
        virtual ~ModuleBase() = default;
        DEFAULT_COPY_MOVE_OPERATIONS(ModuleBase)

        virtual void SetComputeShaderUniforms(const ComputeShader& computeShader) const;
        virtual void SetDrawShaderUniforms(const Shader& drawShader) const;
        virtual void RenderImGui() = 0;
        virtual void RenderDebug(const ParticleSystem& system, Vector2 renderTargetSizeDiff) const;

        GETTER(Types, Type, m_Type)

    private:
        bool_t BeginImGui(Types* enabledModulesInt) const;
        void EndImGui() const;

        Types m_Type = Types::None;

        friend ParticleSystem; // Needs to call BeginImGui() and EndImGui()
    };

    enum class ShapeType : uint8_t
    {
        Circle,
        Line,
        Rectangle,
    };

    enum class ShapeArcMode : uint8_t
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

    class Shape : public ModuleBase
    {
    public:
        using Base = ModuleBase;

        PARTICLE_SYSTEM_MODULE_CONSTRUCTOR(Shape)

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

    private:
        MOUNTAIN_API void SetComputeShaderUniforms(const ComputeShader& computeShader) const override;
        MOUNTAIN_API void RenderImGui() override;
        MOUNTAIN_API void RenderDebug(const ParticleSystem& system, Vector2 renderTargetSizeDiff) const override;
    };

    class MOUNTAIN_API ForceOverLifetime : public ModuleBase
    {
    public:
        using Base = ModuleBase;

        PARTICLE_SYSTEM_MODULE_CONSTRUCTOR(ForceOverLifetime)

        Vector2 force;
        Easing::Type easingType = Easing::Type::Linear;

    private:
        void SetComputeShaderUniforms(const ComputeShader& computeShader) const override;
        void RenderImGui() override;
    };

    class MOUNTAIN_API ColorOverLifetime : public ModuleBase
    {
    public:
        using Base = ModuleBase;

        PARTICLE_SYSTEM_MODULE_CONSTRUCTOR(ColorOverLifetime)

        Color colorMin = Color::White();
        Color colorMax = Color::White();
        Easing::Type easingType = Easing::Type::Linear;

    private:
        void SetComputeShaderUniforms(const ComputeShader& computeShader) const override;
        void RenderImGui() override;
    };

    class MOUNTAIN_API ColorBySpeed : public ModuleBase
    {
    public:
        using Base = ModuleBase;

        PARTICLE_SYSTEM_MODULE_CONSTRUCTOR(ColorBySpeed)

        Color colorMin = Color::White();
        Color colorMax = Color::White();
        float_t speedMin = 0.f;
        float_t speedMax = 1.f;
        Easing::Type easingType = Easing::Type::Linear;

    private:
        void SetComputeShaderUniforms(const ComputeShader& computeShader) const override;
        void RenderImGui() override;
    };

    class Renderer : public ModuleBase
    {
    public:
        using Base = ModuleBase;

        PARTICLE_SYSTEM_MODULE_CONSTRUCTOR(Renderer)

        Pointer<Texture> texture;

    private:
        void RenderImGui() override;
    };
}

ENUM_FLAGS(Mountain::ParticleSystemModules::Types)
