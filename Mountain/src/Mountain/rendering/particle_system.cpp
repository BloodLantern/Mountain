#include "Mountain/rendering/particle_system.hpp"

#include <glad/glad.h>

#include <ImGui/imgui_stdlib.h>

#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/utils/random.hpp"

using namespace Mountain;

namespace
{
    constexpr size_t ParticleStructSize = 48;
}

// ReSharper disable CppObjectMemberMightNotBeInitialized
ParticleSystem::ParticleSystem(const uint32_t maxParticles)
{
    m_BaseUpdateComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "particles/base_update.comp");

    glCreateBuffers(2, &m_AliveSsbo);

    glObjectLabel(GL_BUFFER, m_AliveSsbo, -1, "Particle System Alive SSBO");
    glObjectLabel(GL_BUFFER, m_ParticleSsbo, -1, "Particle System Particle SSBO");

    SetMaxParticles(maxParticles);
}
// ReSharper enable CppObjectMemberMightNotBeInitialized

ParticleSystem::~ParticleSystem()
{
    glUnmapNamedBuffer(m_AliveSsbo);
    glDeleteBuffers(2, &m_AliveSsbo);
}

void ParticleSystem::Update()
{
    const float_t deltaTime = useUnscaledDeltaTime ? Time::GetDeltaTimeUnscaled() : Time::GetDeltaTime();

    m_BaseUpdateComputeShader->SetUniform("deltaTime", deltaTime);
    m_BaseUpdateComputeShader->SetUniform("time", Time::GetTotalTime());
    m_BaseUpdateComputeShader->SetUniform("particleLifetime", particleLifetime);

    WaitBufferSync(m_SyncObject);

    // Spawn new particles if necessary
    if (m_SpawnTimer <= 0.0)
    {
        const double_t spawnDelay = 1.0 / static_cast<double_t>(spawnRate);
        const uint32_t count = static_cast<uint32_t>(std::abs(m_SpawnTimer) / spawnDelay) + 1;

        if (count > 0)
        {
            uint32_t remaining = count;

            for (uint32_t i = 0; i < m_MaxParticles; i++)
            {
                int32_t& particleAlive = m_AliveParticles[i];

                if (particleAlive)
                    continue;

                particleAlive = true;

                if (--remaining <= 0)
                    break;
            }
        }

        m_SpawnTimer += spawnDelay * static_cast<double_t>(count);
    }

    LockBuffer(m_SyncObject);

    glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, &m_AliveSsbo);
    m_BaseUpdateComputeShader->Dispatch(m_MaxParticles);
    glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, nullptr);

    m_SpawnTimer -= deltaTime;
}

void ParticleSystem::Render()
{
    /*for (const Particle& particle : m_Particles)
    {
        if (!particle.alive)
            continue;

        Draw::Point(position + particle.offset, particle.color);
    }*/
}

void ParticleSystem::RenderImGui()
{
    ImGui::PushID(this);
    constexpr size_t zero = 0;
    ImGui::SeparatorText("System settings");
    ImGui::DragFloat2("Position", position.Data());
    ImGui::DragScalar("Spawn rate", ImGuiDataType_U32, &spawnRate, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
    ImGui::BeginDisabled();
    ImGui::DragScalar("Spawn timer", ImGuiDataType_Double, &m_SpawnTimer);

    WaitBufferSync(m_SyncObject);

    uint32_t currentParticles = 0;
    for (uint32_t i = 0; i < m_MaxParticles; i++)
    {
        if (m_AliveParticles[i])
            currentParticles++;
    }

    LockBuffer(m_SyncObject);

    ImGui::DragScalar("Current particles", ImGuiDataType_U32, &currentParticles);
    ImGui::EndDisabled();
    uint32_t maxParticles = m_MaxParticles;
    ImGui::DragScalar("Max particles", ImGuiDataType_U32, &maxParticles, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
    if (maxParticles != m_MaxParticles)
        SetMaxParticles(maxParticles);

    ImGui::SeparatorText("Particles settings");
    ImGui::DragFloat("Lifetime", &particleLifetime, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);

    /*for (const auto& setting : particleSettings)
        setting->RenderImGui(*this);*/
    ImGui::PopID();
}

uint32_t ParticleSystem::GetMaxParticles() const { return m_MaxParticles; }

void ParticleSystem::SetMaxParticles(const uint32_t newMaxParticles)
{
    if (newMaxParticles == 0)
        throw std::invalid_argument{ "ParticleSystem max particle count must be at least 1" };

    m_MaxParticles = newMaxParticles;

    glNamedBufferData(m_ParticleSsbo, static_cast<GLsizeiptr>(ParticleStructSize * newMaxParticles), nullptr, GL_DYNAMIC_COPY);

    if (m_AliveParticles)
    {
        glUnmapNamedBuffer(m_AliveSsbo);

        // As we use an immutable buffer to allow buffer mapping, we need to delete and create the buffer back each time we want to change its size
        glDeleteBuffers(1, &m_AliveSsbo);
        glCreateBuffers(1, &m_AliveSsbo);
    }

    const GLsizeiptr aliveSsboSize = static_cast<GLsizeiptr>(sizeof(int32_t) * newMaxParticles);
    glNamedBufferStorage(m_AliveSsbo, aliveSsboSize, nullptr, GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT);

    m_AliveParticles = static_cast<int32_t*>(glMapNamedBufferRange(m_AliveSsbo, 0, aliveSsboSize, GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT));

    m_BaseUpdateComputeShader->SetUniform("particleCount", newMaxParticles);

    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ParticleSystem::WaitBufferSync(const GLsync syncObject)
{
    if (!syncObject)
        return;

    GLenum waitReturn = GL_UNSIGNALED;
    while (waitReturn != GL_ALREADY_SIGNALED && waitReturn != GL_CONDITION_SATISFIED)
        waitReturn = glClientWaitSync(syncObject, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
}

void ParticleSystem::LockBuffer(GLsync& syncObject)
{
    if (syncObject)
        glDeleteSync(syncObject);
    syncObject = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, GL_NONE);
}
