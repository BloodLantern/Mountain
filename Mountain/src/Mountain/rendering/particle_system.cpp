#include "Mountain/rendering/particle_system.hpp"

#include "ImGui/imgui_stdlib.h"
#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/utils/random.hpp"

Mountain::ParticleSystem::ParticleSystem(const size_t maxParticles)
    : m_MaxParticles(maxParticles)
{
    m_Particles.Resize(maxParticles);
}

void Mountain::ParticleSystem::Update()
{
    const float_t deltaTime = Time::GetDeltaTime();

    // Update all particles
    for (Particle& particle : m_Particles)
    {
        if (!particle.alive)
            continue;

        particle.lifetime -= deltaTime;

        // Particle is dead, no need to update it
        if (particle.lifetime <= 0.f)
        {
            particle.alive = false;
            continue;
        }

        particle.offset += particle.velocity * deltaTime;
        particle.color = Calc::Lerp(particleColorStart, particleColorEnd, 1.f - particle.lifetime / particleLifetime);
    }

    // Spawn new particles if necessary
    if (m_SpawnTimer <= 0.f)
    {
        const size_t count = static_cast<size_t>(Calc::Abs(m_SpawnTimer) / spawnDelay) + 1;

        size_t remaining = count;
        for (Particle& particle : m_Particles)
        {
            if (particle.alive)
                continue;

            particle = {
                .lifetime = particleLifetime,
                .alive = true,
                .offset = Vector2::Zero(),
                .velocity = Random::PointInCircle().Normalized() * 50.f,
                .color = particleColorStart
            };

            if (--remaining <= 0)
                break;
        }

        m_SpawnTimer += spawnDelay * static_cast<float_t>(count);
    }

    m_SpawnTimer -= deltaTime;
}

void Mountain::ParticleSystem::Render()
{
    for (const Particle& particle : m_Particles)
    {
        if (!particle.alive)
            continue;

        Draw::Point(position + particle.offset, particle.color);
    }
}

void Mountain::ParticleSystem::RenderImGui()
{
    ImGui::SeparatorText("System settings");
    ImGui::DragFloat2("Position", position.Data());
    ImGui::DragFloat("Spawn delay", &spawnDelay, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.4f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::BeginDisabled();
    ImGui::DragFloat("Spawn timer", &m_SpawnTimer);
    size_t currentParticles = std::ranges::count_if(m_Particles, [](auto& p) { return p.alive; });
    ImGui::DragScalar("Current particles", ImGuiDataType_U64, &currentParticles);
    ImGui::EndDisabled();
    size_t maxParticles = m_MaxParticles;
    constexpr size_t minParticles = 0;
    ImGui::DragScalar("Max particles", ImGuiDataType_U64, &maxParticles, 1, &minParticles, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
    if (maxParticles != m_MaxParticles)
        SetMaxParticles(maxParticles);

    ImGui::SeparatorText("Particles settings");
    ImGui::DragFloat("Lifetime", &particleLifetime, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::ColorEdit4("Start color", particleColorStart.Data());
    ImGui::ColorEdit4("End color", particleColorEnd.Data());
}

size_t Mountain::ParticleSystem::GetMaxParticles() const { return m_MaxParticles; }

void Mountain::ParticleSystem::SetMaxParticles(const size_t newMaxParticles)
{
    m_MaxParticles = newMaxParticles;
    m_Particles.Resize(newMaxParticles);
}
