#include "Mountain/rendering/particle_system.hpp"

#include <glad/glad.h>

#include <ImGui/imgui_stdlib.h>

#include "Mountain/input/time.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/utils/imgui_utils.hpp"
#include "Mountain/utils/random.hpp"

using namespace Mountain;

namespace
{
    constexpr size_t ParticleStructSize = 48;
}

// ReSharper disable CppObjectMemberMightNotBeInitialized
ParticleSystem::ParticleSystem(const uint32_t maxParticles)
{
    m_UpdateComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "particles/update.comp");
    m_DrawShader = ResourceManager::Get<Shader>(Utils::GetBuiltinShadersPath() + "particles/draw");

    glCreateBuffers(2, &m_AliveSsbo);
    glCreateVertexArrays(1, &m_DrawVao);

    glObjectLabel(GL_BUFFER, m_AliveSsbo, -1, "Particle System Alive SSBO");
    glObjectLabel(GL_BUFFER, m_ParticleSsbo, -1, "Particle System Particle SSBO");
    glObjectLabel(GL_VERTEX_ARRAY, m_DrawVao, -1, "Particle System Draw VAO");

    SetMaxParticles(maxParticles);
}
// ReSharper enable CppObjectMemberMightNotBeInitialized

ParticleSystem::~ParticleSystem()
{
    glUnmapNamedBuffer(m_AliveSsbo);

    glDeleteVertexArrays(1, &m_DrawVao);
    glDeleteBuffers(2, &m_AliveSsbo);
}

void ParticleSystem::Update()
{
    if (!m_Playing)
        return;

    const float_t deltaTime = useUnscaledDeltaTime ? Time::GetDeltaTimeUnscaled() : Time::GetDeltaTime();

    if (m_PlaybackTime >= startDelay)
    {
        SetComputeShaderUniforms(deltaTime);

        for (const auto& module : modules)
            module->SetComputeShaderUniforms(*m_UpdateComputeShader, enabledModules);

        const bool_t spawning = looping || m_PlaybackTime - startDelay < duration;

        if (!spawning && GetCurrentParticles() == 0)
            m_Playing = false;

        // Spawn new particles if necessary
        if (m_SpawnTimer <= 0.0 && spawnRate > 0 && spawning)
            SpawnNewParticles();

        glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, &m_AliveSsbo);
        m_UpdateComputeShader->Dispatch(m_MaxParticles);
        glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, nullptr);

        m_SpawnTimer -= deltaTime;
    }

    m_PlaybackTime += deltaTime;
}

void ParticleSystem::Render()
{
    // TODO - Render using the Draw API as otherwise it would ignore the draw order for depth
    m_DrawShader->SetUniform("projection", Draw::m_ProjectionMatrix * Draw::m_CameraMatrix);

    m_DrawShader->SetUniform("systemPosition", position);
    m_DrawShader->SetUniform("systemRotation", rotation);

    glBindVertexArray(m_DrawVao);
    m_DrawShader->Use();
    glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, &m_AliveSsbo);

    glDrawArraysInstanced(GL_POINTS, 0, 1, static_cast<GLsizei>(m_MaxParticles));

    glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, nullptr);
    m_DrawShader->Unuse();
    glBindVertexArray(0);
}

void ParticleSystem::RenderImGui()
{
    ImGui::PushID(this);

    ImGui::SeparatorText("System controls");
    if (ImGui::Button(m_Playing ? "Pause" : "Play"))
        TogglePlay();
    ImGui::SameLine();
    if (ImGui::Button("Restart"))
        Restart();
    ImGui::SameLine();
    if (ImGui::Button("Stop"))
        Stop();

    constexpr size_t zero = 0;
    ImGui::SeparatorText("System settings");
    ImGui::DragFloat2("Position", position.Data());
    ImGui::DragAngle("Rotation", &rotation);
    ImGui::DragFloat("Duration", &duration);
    ImGui::Checkbox("Looping", &looping);
    ImGui::DragFloat("Start delay", &startDelay, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragScalar("Spawn rate", ImGuiDataType_U32, &spawnRate, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);

    ImGui::SeparatorText("System info");
    ImGui::BeginDisabled();
    uint32_t currentParticles = GetCurrentParticles();
    ImGui::DragScalar("Current particles", ImGuiDataType_U32, &currentParticles);
    ImGui::DragFloat("Playback time", &m_PlaybackTime, 1, 0, 0, "%.2f");
    ImGui::EndDisabled();

    uint32_t maxParticles = m_MaxParticles;
    ImGui::DragScalar("Max particles", ImGuiDataType_U32, &maxParticles, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
    if (maxParticles != m_MaxParticles)
        SetMaxParticles(maxParticles);

    ImGui::SeparatorText("Particles settings");
    ImGui::DragFloat("Lifetime", &particleLifetime, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragFloat("Speed", &particleSpeed);
    ImGui::ColorEdit4("Start color", particleStartColor.Data());

    ImGui::SeparatorText("Modules settings");
    uint32_t* enabledModulesInt = reinterpret_cast<uint32_t*>(&enabledModules);
    ImGui::CheckboxFlags("Enable all modules", enabledModulesInt, static_cast<uint32_t>(ParticleSystemModules::Types::All));
    for (const auto& module : modules)
        module->RenderImGui(enabledModulesInt);

    ImGui::PopID();
}

void ParticleSystem::TogglePlay()
{
    m_Playing = !m_Playing;
}

void ParticleSystem::Restart()
{
    Stop();
    m_Playing = true;
}

void ParticleSystem::Stop()
{
    SetMaxParticles(m_MaxParticles);
    m_Playing = false;
    m_PlaybackTime = 0.f;
}

uint32_t ParticleSystem::GetCurrentParticles()
{
    WaitBufferSync(m_SyncObject);
    uint32_t currentParticles = 0;
    for (uint32_t i = 0; i < m_MaxParticles; i++)
    {
        if (m_AliveParticles[i])
            currentParticles++;
    }
    LockBuffer(m_SyncObject);

    return currentParticles;
}

uint32_t ParticleSystem::GetMaxParticles() const { return m_MaxParticles; }

void ParticleSystem::SetMaxParticles(const uint32_t newMaxParticles)
{
    if (newMaxParticles == 0)
        throw std::invalid_argument{ "ParticleSystem max particle count must be at least 1" };

    m_MaxParticles = newMaxParticles;

    List<uint8_t> emptyData(ParticleStructSize * newMaxParticles);
    glNamedBufferData(m_ParticleSsbo, static_cast<GLsizeiptr>(ParticleStructSize * newMaxParticles), emptyData.GetData(), GL_DYNAMIC_COPY);
    emptyData.Resize(0);

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

    m_UpdateComputeShader->SetUniform("particleCount", newMaxParticles);
    m_DrawShader->SetUniform("particleCount", newMaxParticles);

    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

bool_t ParticleSystem::IsPlaying() const { return m_Playing; }

void ParticleSystem::SetComputeShaderUniforms(float_t deltaTime) const
{
    m_UpdateComputeShader->SetUniform("deltaTime", deltaTime);
    m_UpdateComputeShader->SetUniform("time", Time::GetTotalTime());

    m_UpdateComputeShader->SetUniform("particleLifetime", particleLifetime);
    m_UpdateComputeShader->SetUniform("particleSpeed", particleSpeed);
    m_UpdateComputeShader->SetUniform("particleStartColor", particleStartColor);

    m_UpdateComputeShader->SetUniform("enabledModules", static_cast<uint32_t>(enabledModules));
}

void ParticleSystem::SpawnNewParticles()
{
    const double_t spawnDelay = 1.0 / static_cast<double_t>(spawnRate);
    const uint32_t count = static_cast<uint32_t>(std::abs(m_SpawnTimer) / spawnDelay) + 1;

    if (count > 0)
    {
        uint32_t remaining = count;

        WaitBufferSync(m_SyncObject);

        for (uint32_t i = 0; i < m_MaxParticles; i++)
        {
            int32_t& particleAlive = m_AliveParticles[i];

            if (particleAlive)
                continue;

            particleAlive = true;

            if (--remaining <= 0)
                break;
        }

        LockBuffer(m_SyncObject);
    }

    m_SpawnTimer += spawnDelay * static_cast<double_t>(count);
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
