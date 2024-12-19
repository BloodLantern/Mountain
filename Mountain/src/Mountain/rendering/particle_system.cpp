#include "Mountain/rendering/particle_system.hpp"

#include <glad/glad.h>

#include <ImGui/imgui_stdlib.h>

#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/utils/random.hpp"

namespace
{
    constexpr size_t ParticleStructSize = 48;
}

Mountain::ParticleSystem::ParticleSystem(const size_t maxParticles)
{
    glCreateBuffers(1, &m_Ssbo);

    glObjectLabel(GL_BUFFER, m_Ssbo, -1, "Particle System SSBO");

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Ssbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_Ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    SetMaxParticles(maxParticles);
}

Mountain::ParticleSystem::~ParticleSystem()
{
    glDeleteBuffers(1, &m_Ssbo);
}

void Mountain::ParticleSystem::LoadResources()
{
    m_BaseUpdateComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "particles/base_update.comp");
}

void Mountain::ParticleSystem::Update()
{
    const float_t deltaTime = useUnscaledDeltaTime ? Time::GetDeltaTimeUnscaled() : Time::GetDeltaTime();

    m_BaseUpdateComputeShader->SetUniform("particleCount", static_cast<int32_t>(m_MaxParticles));

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Ssbo);
    m_BaseUpdateComputeShader->Dispatch(static_cast<uint32_t>(m_MaxParticles));
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

/*
    // Spawn new particles if necessary
    if (m_SpawnTimer <= 0.0)
    {
        const double_t spawnDelay = 1.0 / static_cast<double_t>(spawnRate);
        const size_t count = static_cast<size_t>(std::abs(m_SpawnTimer) / spawnDelay) + 1;

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
                .color = Color::White()
            };

            if (--remaining <= 0)
                break;
        }

        m_SpawnTimer += spawnDelay * static_cast<double_t>(count);
    }

    // Update all particles
    for (Particle& particle : m_Particles)
    {
        if (!particle.alive)
            continue;

        // Particle is dead, no need to update it
        if (particle.lifetime <= 0.f)
        {
            particle.alive = false;
            continue;
        }

        particle.offset += particle.velocity * deltaTime;

        for (const auto& setting : particleSettings)
        {
            if (setting->enabled)
                setting->Update(*this, particle, deltaTime);
        }

        particle.lifetime -= deltaTime;
    }

    m_SpawnTimer -= deltaTime;*/
}

void Mountain::ParticleSystem::Render()
{
    /*for (const Particle& particle : m_Particles)
    {
        if (!particle.alive)
            continue;

        Draw::Point(position + particle.offset, particle.color);
    }*/
}

void Mountain::ParticleSystem::RenderImGui()
{
    ImGui::PushID(this);
    constexpr size_t zero = 0;
    ImGui::SeparatorText("System settings");
    ImGui::DragFloat2("Position", position.Data());
    ImGui::DragScalar("Spawn rate", ImGuiDataType_U64, &spawnRate, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
    ImGui::BeginDisabled();
    ImGui::DragScalar("Spawn timer", ImGuiDataType_Double, &m_SpawnTimer);
    /*size_t currentParticles = std::ranges::count_if(m_Particles, [](auto& p) { return p.alive; });
    ImGui::DragScalar("Current particles", ImGuiDataType_U64, &currentParticles);*/
    ImGui::EndDisabled();
    size_t maxParticles = m_MaxParticles;
    ImGui::DragScalar("Max particles", ImGuiDataType_U64, &maxParticles, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
    if (maxParticles != m_MaxParticles)
        SetMaxParticles(maxParticles);

    ImGui::SeparatorText("Particles settings");
    ImGui::DragFloat("Lifetime", &particleLifetime, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);

    /*for (const auto& setting : particleSettings)
        setting->RenderImGui(*this);*/
    ImGui::PopID();
}

size_t Mountain::ParticleSystem::GetMaxParticles() const { return m_MaxParticles; }

void Mountain::ParticleSystem::SetMaxParticles(const size_t newMaxParticles)
{
    m_MaxParticles = newMaxParticles;

    glNamedBufferData(m_Ssbo, static_cast<GLsizeiptr>(ParticleStructSize * m_MaxParticles), nullptr, GL_DYNAMIC_COPY);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    //m_Particles.Resize(newMaxParticles);
}
