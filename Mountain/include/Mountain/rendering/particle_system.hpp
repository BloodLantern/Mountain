#pragma once

#include <Maths/vector2.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/particle_system_settings.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/list.hpp"

BEGIN_MOUNTAIN

struct Particle
{
    float_t lifetime = 1.f;
    bool_t alive = false;

    Vector2 offset;
    Vector2 velocity;
    Color color;
};

class ParticleSystem
{
public:
    // Particle system settings

    Vector2 position;
    /// @brief The amount of particles spawned per second
    size_t spawnRate = 10;
    bool_t useUnscaledDeltaTime = false;
    float_t duration = 5.f;
    bool_t looping = true;

    // Particle settings

    float_t particleLifetime = 1.f;

    List<std::shared_ptr<ParticleSystemSettings::Base>> particleSettings;

    MOUNTAIN_API ParticleSystem() = default;
    MOUNTAIN_API explicit ParticleSystem(size_t maxParticles);

    MOUNTAIN_API void Update();
    MOUNTAIN_API void Render();
    MOUNTAIN_API void RenderImGui();

    [[nodiscard]]
    MOUNTAIN_API size_t GetMaxParticles() const;
    MOUNTAIN_API void SetMaxParticles(size_t newMaxParticles);

private:
    size_t m_MaxParticles = 0;

    List<Particle> m_Particles{};

    double_t m_SpawnTimer = 0.0;
};

END_MOUNTAIN
