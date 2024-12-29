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
    constexpr size_t GpuParticleStructSize = 48;
}

// ReSharper disable CppObjectMemberMightNotBeInitialized
ParticleSystem::ParticleSystem(const uint32_t maxParticles)
{
    m_UpdateComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "particles/update.comp");
    m_DrawShader = ResourceManager::Get<Shader>(Utils::GetBuiltinShadersPath() + "particles/draw");

    modules.AddRange(
        {
            std::make_shared<ParticleSystemModules::Shape>(),
        }
    );

    glCreateBuffers(2, &m_LiveSsbo);
    glCreateVertexArrays(1, &m_DrawVao);

    glObjectLabel(GL_BUFFER, m_LiveSsbo, -1, "Particle System Live SSBO");
    glObjectLabel(GL_BUFFER, m_ParticleSsbo, -1, "Particle System Particle SSBO");
    glObjectLabel(GL_VERTEX_ARRAY, m_DrawVao, -1, "Particle System Draw VAO");

    SetMaxParticles(maxParticles);
}
// ReSharper enable CppObjectMemberMightNotBeInitialized

ParticleSystem::~ParticleSystem()
{
    glUnmapNamedBuffer(m_LiveSsbo);

    glDeleteVertexArrays(1, &m_DrawVao);
    glDeleteBuffers(2, &m_LiveSsbo);
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
        if (spawning)
            SpawnNewParticles();

        glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, &m_LiveSsbo);
        m_UpdateComputeShader->Dispatch(m_MaxParticles);
        glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, nullptr);

        m_SpawnTimer -= deltaTime;
    }

    m_LastPosition = position;
    m_LastPlaybackTime = m_PlaybackTime;

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
    glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, &m_LiveSsbo);

    glDrawArraysInstanced(GL_POINTS, 0, 1, static_cast<GLsizei>(m_MaxParticles));

    glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, nullptr);
    m_DrawShader->Unuse();
    glBindVertexArray(0);
}

void ParticleSystem::RenderImGui()
{
    ImGui::PushID(this);

    ImGuiUtils::PushSeparatorText("System controls");
    const bool_t systemDead = !(looping || m_PlaybackTime - startDelay < duration) && GetCurrentParticles() == 0;
    if (systemDead)
        ImGui::BeginDisabled();
    if (ImGui::Button(m_Playing ? "Pause" : "Play"))
        TogglePlay();
    if (systemDead)
        ImGui::EndDisabled();
    ImGui::SameLine();
    if (ImGui::Button("Restart"))
        Restart();
    ImGui::SameLine();
    if (ImGui::Button("Stop"))
        Stop();
    ImGuiUtils::PopSeparatorText();

    constexpr size_t zero = 0;
    ImGuiUtils::PushSeparatorText("System settings");
    ImGui::DragFloat2("Position", position.Data());
    ImGui::DragAngle("Rotation", &rotation);
    ImGui::DragFloat("Duration", &duration);
    ImGui::Checkbox("Looping", &looping);
    ImGui::DragFloat("Start delay", &startDelay, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);

    uint32_t maxParticles = m_MaxParticles;
    ImGui::DragScalar("Max particles", ImGuiDataType_U32, &maxParticles, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
    if (maxParticles != m_MaxParticles)
        SetMaxParticles(maxParticles);
    ImGuiUtils::PopSeparatorText();

    ImGuiUtils::PushSeparatorText("System info");
    ImGui::BeginDisabled();
    uint32_t currentParticles = GetCurrentParticles();
    ImGui::DragScalar("Current particles", ImGuiDataType_U32, &currentParticles);
    ImGui::DragFloat("Playback time", &m_PlaybackTime, 1, 0, 0, "%.2f");
    ImGui::EndDisabled();
    ImGuiUtils::PopSeparatorText();

    ImGuiUtils::PushSeparatorText("Emission settings");
    ImGui::DragFloat("Rate over time", &emissionRateOverTime, 1.f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragFloat("Rate over distance", &emissionRateOverDistance, 1.f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::Text("Bursts: %llu", emissionBursts.GetSize());
    ImGui::SameLine();
    if (ImGui::Button("-"))
        emissionBursts.Pop();
    ImGui::SameLine();
    if (ImGui::Button("+"))
        emissionBursts.Emplace();
    if (ImGui::BeginTable("burstsTable", 7, ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchSame))
    {
        ImGui::TableSetupColumn("Index");
        ImGui::TableSetupColumn("Time");
        ImGui::TableSetupColumn("Count");
        ImGui::TableSetupColumn("Cycles");
        ImGui::TableSetupColumn("Interval");
        ImGui::TableSetupColumn("Probability");
        ImGui::TableSetupColumn("Remove");

        ImGui::TableHeadersRow();

        m_ImGuiParticleBurstTimeHeld = false;
        for (size_t i = 0; i < emissionBursts.GetSize(); i++)
        {
            ParticleSystemBurst& burst = emissionBursts[i];

            ImGui::PushID(&burst);

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%llu", i);

            ImGui::TableSetColumnIndex(1);
            ImGuiUtils::SetNextItemWidthAvail();
            ImGui::DragFloat("##time", &burst.time, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.3f", ImGuiSliderFlags_AlwaysClamp);
            if (ImGui::IsItemActive())
                m_ImGuiParticleBurstTimeHeld = true;

            ImGui::TableSetColumnIndex(2);
            ImGuiUtils::SetNextItemWidthAvail();
            ImGui::DragScalar("##count", ImGuiDataType_U32, &burst.count, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);

            ImGui::TableSetColumnIndex(3);
            ImGuiUtils::SetNextItemWidthAvail();
            ImGui::DragScalar("##cycles", ImGuiDataType_U32, &burst.cycles, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
            ImGui::SetItemTooltip("If set to 0, this will be infinite");

            ImGui::TableSetColumnIndex(4);
            ImGuiUtils::SetNextItemWidthAvail();
            ImGui::DragFloat("##interval", &burst.interval, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.3f", ImGuiSliderFlags_AlwaysClamp);

            ImGui::TableSetColumnIndex(5);
            ImGuiUtils::SetNextItemWidthAvail();
            ImGui::DragFloat("##probability", &burst.probability, 0.01f, 0.f, 1.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

            ImGui::TableSetColumnIndex(6);
            if (ImGui::Button("-", ImVec2{ ImGui::GetContentRegionAvail().x, 0.f }))
                emissionBursts.RemoveAt(i--);

            ImGui::PopID();
        }

        ImGui::EndTable();
    }
    ImGuiUtils::PopSeparatorText();

    ImGuiUtils::PushSeparatorText("Particles settings");
    ImGui::DragFloat("Lifetime", &particleLifetime, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragFloat("Speed", &particleSpeed);
    ImGui::ColorEdit4("Start color", particleStartColor.Data());
    ImGuiUtils::PopSeparatorText();

    ImGuiUtils::PushSeparatorText("Modules settings");
    uint32_t* enabledModulesInt = reinterpret_cast<uint32_t*>(&enabledModules);
    ImGui::CheckboxFlags("Enable all modules", enabledModulesInt, static_cast<uint32_t>(ParticleSystemModules::Types::All));
    for (const auto& module : modules)
        module->RenderImGui(enabledModulesInt);
    ImGuiUtils::PopSeparatorText();

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
    m_LastPlaybackTime = 0.f;
    m_SpawnTimer = 0.f;
}

uint32_t ParticleSystem::GetCurrentParticles()
{
    WaitBufferSync(m_SyncObject);
    uint32_t currentParticles = 0;
    for (uint32_t i = 0; i < m_MaxParticles; i++)
    {
        if (m_LiveParticles[i])
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

    List<uint8_t> emptyData(GpuParticleStructSize * newMaxParticles);
    glNamedBufferData(m_ParticleSsbo, static_cast<GLsizeiptr>(GpuParticleStructSize * newMaxParticles), emptyData.GetData(), GL_DYNAMIC_COPY);
    emptyData.Resize(0);

    if (m_LiveParticles)
    {
        glUnmapNamedBuffer(m_LiveSsbo);

        // As we use an immutable buffer to allow buffer mapping, we need to delete and create the buffer back each time we want to change its size
        glDeleteBuffers(1, &m_LiveSsbo);
        glCreateBuffers(1, &m_LiveSsbo);
    }

    const GLsizeiptr aliveSsboSize = static_cast<GLsizeiptr>(sizeof(int32_t) * newMaxParticles);
    glNamedBufferStorage(m_LiveSsbo, aliveSsboSize, nullptr, GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT);

    m_LiveParticles = static_cast<int32_t*>(glMapNamedBufferRange(m_LiveSsbo, 0, aliveSsboSize, GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT));

    m_UpdateComputeShader->SetUniform("particleCount", newMaxParticles);
    m_DrawShader->SetUniform("particleCount", newMaxParticles);

    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

bool_t ParticleSystem::IsPlaying() const { return m_Playing; }

void ParticleSystem::SetComputeShaderUniforms(const float_t deltaTime) const
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
    uint32_t overTimeCount = 0, overDistanceCount = 0, burstCount = 0;
    if (m_SpawnTimer <= 0.f && emissionRateOverTime > 0.f)
    {
        const double_t spawnDelay = 1.0 / static_cast<double_t>(emissionRateOverTime);
        overTimeCount = static_cast<uint32_t>(std::abs(m_SpawnTimer) / spawnDelay) + 1;
        m_SpawnTimer += spawnDelay * static_cast<double_t>(overTimeCount);
    }

    if (position != m_LastPosition && emissionRateOverDistance > 0.f)
    {
        const float_t lastFrameDistance = (position - m_LastPosition).Length();
        overDistanceCount = static_cast<uint32_t>(Calc::Round(lastFrameDistance * emissionRateOverDistance));
    }

    if (!emissionBursts.Empty() && !m_ImGuiParticleBurstTimeHeld)
    {
        emissionBursts.Sort(
            [](const ParticleSystemBurst& left, const ParticleSystemBurst& right) -> bool_t
            {
                return left.time < right.time;
            }
        );

        for (const ParticleSystemBurst& burst : emissionBursts)
        {
            if (burst.time > m_PlaybackTime)
                break; // Because the list is now sorted by time, instead of continuing we can just break out of the loop

            if (burst.cycles == 0 && burst.interval == 0.f)
                throw std::logic_error{ "A ParticleSystemBurst cannot have both its cycles and interval at 0" };

            const float_t cycles = burst.cycles == 0 ? std::numeric_limits<float_t>::infinity() : static_cast<float_t>(burst.cycles);
            const float_t latestCycleTime = burst.time + (cycles - 1.f) * burst.interval;
            const bool_t timeCondition = latestCycleTime >= m_LastPlaybackTime;

            if (!timeCondition)
                continue;

            const float_t playbackTime = m_PlaybackTime - burst.time, lastPlaybackTime = m_LastPlaybackTime - burst.time;
            const bool_t intervalCondition = lastPlaybackTime <= 0.f || burst.interval == 0.f || Calc::OnInterval(playbackTime, lastPlaybackTime, burst.interval); // FIXME - OnInterval
            if (!intervalCondition)
                continue;

            const int32_t spawnCount = static_cast<int32_t>(std::clamp(
                                           Calc::Round((playbackTime - lastPlaybackTime) / burst.interval),
                                           0.f,
                                           cycles
                                       )) + 1;

            for (int32_t i = 0; i < spawnCount; i++)
            {
                if (Random::Chance(burst.probability))
                    burstCount += burst.count;
            }
        }
    }

    const uint32_t totalCount = overTimeCount + overDistanceCount + burstCount;

    if (totalCount > 0)
    {
        uint32_t remaining = totalCount;

        WaitBufferSync(m_SyncObject);

        for (uint32_t i = 0; i < m_MaxParticles; i++)
        {
            int32_t& liveParticle = m_LiveParticles[i];

            if (liveParticle)
                continue;

            liveParticle = true;

            if (--remaining <= 0)
                break;
        }

        LockBuffer(m_SyncObject);
    }
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
