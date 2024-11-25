#pragma once

#include <Maths/vector2.hpp>

#include "Mountain/core.hpp"
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
    float_t spawnDelay = 0.1f;

    // Particle settings

    float_t particleLifetime = 1.f;
    Color particleColorStart = Color::White();
    Color particleColorEnd = Color::Transparent();

    MOUNTAIN_API explicit ParticleSystem(size_t maxParticles);

    MOUNTAIN_API void Update();
    MOUNTAIN_API void Render();
    MOUNTAIN_API void RenderImGui();

    [[nodiscard]]
    MOUNTAIN_API size_t GetMaxParticles() const;
    MOUNTAIN_API void SetMaxParticles(size_t newMaxParticles);

private:
    size_t m_MaxParticles;

    List<Particle> m_Particles;

    float_t m_SpawnTimer = 0.f;
};

END_MOUNTAIN
