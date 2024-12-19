#pragma once

#include "Mountain/core.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/utils.hpp"
/*
namespace Mountain
{
    struct Particle;
    class ParticleSystem;
}

namespace Mountain::ParticleSystemSettings
{
    class Base
    {
    public:
        bool_t enabled = false;

        Base() = default;
        virtual ~Base() = default;

        DEFAULT_COPY_MOVE_OPERATIONS(Base)

        MOUNTAIN_API virtual void Update(ParticleSystem& system, Particle& particle, float_t deltaTime) const = 0;
        MOUNTAIN_API virtual void RenderImGui(ParticleSystem& system) = 0;

    protected:
        MOUNTAIN_API virtual bool_t RenderImGuiHeader(std::string_view typeName);
        MOUNTAIN_API virtual void RenderImGuiFooter();
    };

    class ColorOverLifetime : public Base
    {
    public:
        Color start = Color::White();
        Color end = Color::Transparent();

        Easing::Easer function = Utils::Identity<float_t>;

        MOUNTAIN_API void Update(ParticleSystem& system, Particle& particle, float_t deltaTime) const override;
        MOUNTAIN_API void RenderImGui(ParticleSystem& system) override;
    };

    class Acceleration : public Base
    {
    public:
        Vector2 acceleration;

        MOUNTAIN_API void Update(ParticleSystem& system, Particle& particle, float_t deltaTime) const override;
        MOUNTAIN_API void RenderImGui(ParticleSystem& system) override;
    };
}
*/