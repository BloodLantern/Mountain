#pragma once

#include <Maths/vector2.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/particle_system_settings.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/list.hpp"

namespace Mountain
{
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

        //List<std::shared_ptr<ParticleSystemSettings::Base>> particleSettings;

        MOUNTAIN_API ParticleSystem() = default;
        MOUNTAIN_API explicit ParticleSystem(size_t maxParticles);
        MOUNTAIN_API virtual ~ParticleSystem();

        DEFAULT_COPY_MOVE_OPERATIONS(ParticleSystem)

        MOUNTAIN_API void LoadResources();
        MOUNTAIN_API void Update();
        MOUNTAIN_API void Render();
        MOUNTAIN_API void RenderImGui();

        [[nodiscard]]
        MOUNTAIN_API size_t GetMaxParticles() const;
        MOUNTAIN_API void SetMaxParticles(size_t newMaxParticles);

    private:
        size_t m_MaxParticles = 0;

        //List<Particle> m_Particles{};

        double_t m_SpawnTimer = 0.0;

        Pointer<ComputeShader> m_BaseUpdateComputeShader;
        uint32_t m_Ssbo;
    };
}
