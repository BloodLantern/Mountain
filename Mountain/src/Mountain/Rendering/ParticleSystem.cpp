#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Rendering/ParticleSystem.hpp"

#include <glad/glad.h>

#include <ImGui/imgui_stdlib.h>

#include "Mountain/Input/Time.hpp"
#include "Mountain/Rendering/Draw.hpp"
#include "Mountain/Rendering/Renderer.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/ImGuiUtils.hpp"
#include "Mountain/Utils/Random.hpp"

using namespace Mountain;

namespace
{
    constexpr size_t GpuParticleStructSize = 48;
}

ParticleSystem::ParticleSystem()
    : ParticleSystem{1000}
{
}

// ReSharper disable CppObjectMemberMightNotBeInitialized
ParticleSystem::ParticleSystem(const uint32_t maxParticles)
{
    m_UpdateComputeShader = ResourceManager::Get<ComputeShader>(Utils::GetBuiltinShadersPath() + "particles/update.comp");
    m_DrawShader = ResourceManager::Get<Shader>(Utils::GetBuiltinShadersPath() + "particles/draw_point");

    m_LiveSsbo.Create();
    m_ParticleSsbo.Create();

    m_LiveSsbo.SetDebugName("Particle System Live SSBO");
    m_ParticleSsbo.SetDebugName("Particle System Particle SSBO");

    SetMaxParticles(maxParticles);
}
// ReSharper enable CppObjectMemberMightNotBeInitialized

ParticleSystem::~ParticleSystem()
{
    glUnmapNamedBuffer(m_LiveSsbo.GetId());

    m_LiveSsbo.Delete();
    m_ParticleSsbo.Delete();
}

void ParticleSystem::Update()
{
    Update(useUnscaledDeltaTime ? Time::GetDeltaTimeUnscaled() : Time::GetDeltaTime());
}

void ParticleSystem::Render()
{
    Draw::Flush();

    m_RenderTargetSize = Renderer::GetCurrentRenderTarget().GetSize();

    if (enabledModules & ParticleSystemModules::Types::Renderer && m_RendererModule)
    {
        static bool_t lastUseTexture = false;

        const bool_t useTexture = m_RendererModule->texture != nullptr;

        if (lastUseTexture != useTexture)
            m_DrawShader = ResourceManager::Get<Shader>(Utils::GetBuiltinShadersPath() + (useTexture ? "particles/draw" : "particles/draw_point"));

        m_DrawShader->SetUniform("particleCount", m_MaxParticles);

        if (useTexture)
            m_DrawShader->SetUniform("imageSizeNormalized", m_RendererModule->texture->GetSize() / m_RenderTargetSize);

        m_DrawShader->SetUniform("projection", Draw::m_ProjectionMatrix * Draw::m_CameraMatrix);

        m_DrawShader->SetUniform("systemPosition", position);
        m_DrawShader->SetUniform("systemRotation", Vector2{std::cos(rotation), std::sin(rotation)});

        if (useTexture)
            Graphics::BindTexture(m_RendererModule->texture->GetId());

        BindVertexArray(Draw::m_ParticleVao);
        m_DrawShader->Use();
        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 0, m_LiveSsbo);
        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 1, m_ParticleSsbo);

        DrawArraysInstanced(Graphics::DrawMode::Points, 0, 1, static_cast<int32_t>(m_MaxParticles));

        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 1, 0);
        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 0, 0);
        m_DrawShader->Unuse();
        Graphics::BindVertexArray(0);

        if (useTexture)
            Graphics::BindTexture(0);

        lastUseTexture = useTexture;
    }
}

void ParticleSystem::RenderImGui()
{
    ImGui::PushID(this);

    uint8_t* dataCopy = CreateRawDataCopy();

    if (ImGuiUtils::PushSeparatorText("System controls"))
    {
        const bool_t complete = IsComplete();
        if (complete)
            ImGui::BeginDisabled();
        if (ImGui::Button(m_Playing ? "Pause" : "Play"))
            TogglePlay();
        if (complete)
            ImGui::EndDisabled();
        ImGui::SameLine();
        if (ImGui::Button("Restart"))
            Restart();
        ImGui::SameLine();
        if (ImGui::Button("Stop"))
            Stop();

        ImGuiUtils::PopSeparatorText();
    }

    constexpr size_t zero = 0;
    if (ImGuiUtils::PushSeparatorText("System settings"))
    {
        ImGui::DragFloat2("Position", position.Data());
        ImGui::DragAngle("Rotation", &rotation);
        ImGui::DragFloat("Duration", &duration, 0.1f);
        ImGui::Checkbox("Looping", &looping);
        ImGui::DragFloat("Start delay", &startDelay, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);

        uint32_t maxParticles = m_MaxParticles;
        ImGui::DragScalar("Max particles", ImGuiDataType_U32, &maxParticles, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
        if (maxParticles != m_MaxParticles)
            SetMaxParticles(maxParticles);

        ImGuiUtils::PopSeparatorText();
    }

    if (ImGuiUtils::PushSeparatorText("System info"))
    {
        ImGui::BeginDisabled();
        uint32_t currentParticles = GetCurrentParticles();
        ImGui::DragScalar("Current particles", ImGuiDataType_U32, &currentParticles);
        ImGui::DragFloat("Playback time", &m_PlaybackTime, 1, 0, 0, "%.2f");
        ImGui::EndDisabled();

        ImGuiUtils::PopSeparatorText();
    }

    if (ImGuiUtils::PushSeparatorText("Emission settings"))
    {
        ImGui::DragFloat("Rate over time", &emissionRateOverTime, 1.f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::DragFloat("Rate over distance", &emissionRateOverDistance, 1.f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Text("Bursts: %llu", emissionBursts.GetSize());
        ImGui::SameLine();
        if (ImGui::Button("-"))
            emissionBursts.RemoveLast();
        ImGui::SameLine();
        if (ImGui::Button("+"))
            emissionBursts.Emplace();
        if (emissionBursts.GetSize() > 0)
        {
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

                m_GuiParticleBurstTimeHeld = false;
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
                        m_GuiParticleBurstTimeHeld = true;

                    ImGui::TableSetColumnIndex(2);
                    ImGuiUtils::SetNextItemWidthAvail();
                    ImGui::DragScalar("##count", ImGuiDataType_U32, &burst.count, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);

                    ImGui::TableSetColumnIndex(3);
                    ImGuiUtils::SetNextItemWidthAvail();
                    ImGui::DragScalar("##cycles", ImGuiDataType_U32, &burst.cycles, 1, &zero, nullptr, nullptr, ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SetItemTooltip("If set to 0, this will be infinite");

                    ImGui::TableSetColumnIndex(4);
                    ImGuiUtils::SetNextItemWidthAvail();
                    ImGui::DragFloat("##interval", &burst.interval, 0.01f, Calc::Zero, std::numeric_limits<float_t>::max(), "%.3f", ImGuiSliderFlags_AlwaysClamp);

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
        }

        ImGuiUtils::PopSeparatorText();
    }

    if (ImGuiUtils::PushSeparatorText("Particles settings"))
    {
        ImGui::DragFloat("Lifetime", &particleLifetime, 0.01f, 0.f, std::numeric_limits<float_t>::max(), "%.2f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::DragFloat("Speed", &particleSpeed);
        ImGui::ColorEdit4("Start color", particleStartColor.Data());
        ImGui::DragFloat("Start size", &particleStartSize);

        ImGuiUtils::PopSeparatorText();
    }

    if (ImGuiUtils::PushSeparatorText("Modules settings"))
    {
        uint32_t* enabledModulesInt = reinterpret_cast<uint32_t*>(&enabledModules);
        ImGui::CheckboxFlags("Enable all modules", enabledModulesInt, static_cast<uint32_t>(ParticleSystemModules::Types::All));
        for (const auto& module : m_Modules)
        {
            if (!module->BeginImGui(&enabledModules))
                continue;
            module->RenderImGui();
            module->EndImGui();
        }

        ImGuiUtils::PopSeparatorText();
    }

    if (CheckAndDeleteRawDataCopy(dataCopy))
    {
        const float_t oldPlaybackTime = std::min(m_PlaybackTime, duration) + Calc::Modulo(m_PlaybackTime, duration);
        Restart();
        while (m_PlaybackTime < oldPlaybackTime)
            Update(std::min(oldPlaybackTime - m_PlaybackTime, useUnscaledDeltaTime ? Time::GetDeltaTimeUnscaled() : Time::GetDeltaTime()));
    }

    ImGui::PopID();
}

void ParticleSystem::RenderDebug()
{
    const Vector2 renderTargetSizeDiff = Renderer::GetCurrentRenderTarget().GetSize() / m_RenderTargetSize;
    for (const auto& module : m_Modules)
    {
        if (enabledModules & module->GetType())
            module->RenderDebug(*this, renderTargetSizeDiff);
    }
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
    SetMaxParticles(m_MaxParticles); // Reset the buffers
    m_Playing = false;
    m_PlaybackTime = 0.f;
    m_LastPlaybackTime = 0.f;
    m_SpawnTimer = 0.f;
}

std::shared_ptr<ParticleSystemModules::ModuleBase> ParticleSystem::AddModule(const ParticleSystemModules::Types type)
{
    std::shared_ptr<ParticleSystemModules::ModuleBase> result;

    switch (type)
    {
        case ParticleSystemModules::Types::Shape: result = std::make_shared<ParticleSystemModules::Shape>(); break;
        case ParticleSystemModules::Types::VelocityOverLifetime: result = std::make_shared<ParticleSystemModules::VelocityOverLifetime>(); break;
        // case ParticleSystemModules::Types::LimitVelocityOverLifetime: result = std::make_shared<ParticleSystemModules::LimitVelocityOverLifetime>(); break;
        // case ParticleSystemModules::Types::InheritVelocity: result = std::make_shared<ParticleSystemModules::InheritVelocity>(); break;
        // case ParticleSystemModules::Types::LifetimeByEmitterSpeed: result = std::make_shared<ParticleSystemModules::LifetimeByEmitterSpeed>(); break;
        case ParticleSystemModules::Types::ForceOverLifetime: result = std::make_shared<ParticleSystemModules::ForceOverLifetime>(); break;
        case ParticleSystemModules::Types::ColorOverLifetime: result = std::make_shared<ParticleSystemModules::ColorOverLifetime>(); break;
        case ParticleSystemModules::Types::ColorBySpeed: result = std::make_shared<ParticleSystemModules::ColorBySpeed>(); break;
        // case ParticleSystemModules::Types::SizeOverLifetime: result = std::make_shared<ParticleSystemModules::SizeOverLifetime>(); break;
        // case ParticleSystemModules::Types::SizeBySpeed: result = std::make_shared<ParticleSystemModules::SizeBySpeed>(); break;
        // case ParticleSystemModules::Types::RotationOverLifetime: result = std::make_shared<ParticleSystemModules::RotationOverLifetime>(); break;
        // case ParticleSystemModules::Types::RotationBySpeed: result = std::make_shared<ParticleSystemModules::RotationBySpeed>(); break;
        // case ParticleSystemModules::Types::Noise: result = std::make_shared<ParticleSystemModules::Noise>(); break;
        // case ParticleSystemModules::Types::Collision: result = std::make_shared<ParticleSystemModules::Collision>(); break;
        // case ParticleSystemModules::Types::SubEmitters: result = std::make_shared<ParticleSystemModules::SubEmitters>(); break;
        // case ParticleSystemModules::Types::TextureSheetAnimation: result = std::make_shared<ParticleSystemModules::TextureSheetAnimation>(); break;
        // case ParticleSystemModules::Types::Lights: result = std::make_shared<ParticleSystemModules::Lights>(); break;
        // case ParticleSystemModules::Types::Trails: result = std::make_shared<ParticleSystemModules::Trails>(); break;
        case ParticleSystemModules::Types::Renderer: result = std::make_shared<ParticleSystemModules::Renderer>(); break;

        default: THROW(ArgumentException{"Invalid particle system type", "type"});
    }

    AddModule(result, true);

    return result;
}

List<std::shared_ptr<ParticleSystemModules::ModuleBase>> ParticleSystem::AddModules(const ParticleSystemModules::Types types)
{
    List<std::shared_ptr<ParticleSystemModules::ModuleBase>> result;

    if (types & ParticleSystemModules::Types::Shape) result.Add(std::make_shared<ParticleSystemModules::Shape>());
    if (types & ParticleSystemModules::Types::VelocityOverLifetime) result.Add(std::make_shared<ParticleSystemModules::VelocityOverLifetime>());
    // if (types & ParticleSystemModules::Types::LimitVelocityOverLifetime) result.Add(std::make_shared<ParticleSystemModules::LimitVelocityOverLifetime>());
    // if (types & ParticleSystemModules::Types::InheritVelocity) result.Add(std::make_shared<ParticleSystemModules::InheritVelocity>());
    // if (types & ParticleSystemModules::Types::LifetimeByEmitterSpeed) result.Add(std::make_shared<ParticleSystemModules::LifetimeByEmitterSpeed>());
    if (types & ParticleSystemModules::Types::ForceOverLifetime) result.Add(std::make_shared<ParticleSystemModules::ForceOverLifetime>());
    if (types & ParticleSystemModules::Types::ColorOverLifetime) result.Add(std::make_shared<ParticleSystemModules::ColorOverLifetime>());
    if (types & ParticleSystemModules::Types::ColorBySpeed) result.Add(std::make_shared<ParticleSystemModules::ColorBySpeed>());
    // if (types & ParticleSystemModules::Types::SizeOverLifetime) result.Add(std::make_shared<ParticleSystemModules::SizeOverLifetime>());
    // if (types & ParticleSystemModules::Types::SizeBySpeed) result.Add(std::make_shared<ParticleSystemModules::SizeBySpeed>());
    // if (types & ParticleSystemModules::Types::RotationOverLifetime) result.Add(std::make_shared<ParticleSystemModules::RotationOverLifetime>());
    // if (types & ParticleSystemModules::Types::RotationBySpeed) result.Add(std::make_shared<ParticleSystemModules::RotationBySpeed>());
    // if (types & ParticleSystemModules::Types::Noise) result.Add(std::make_shared<ParticleSystemModules::Noise>());
    // if (types & ParticleSystemModules::Types::Collision) result.Add(std::make_shared<ParticleSystemModules::Collision>());
    // if (types & ParticleSystemModules::Types::SubEmitters) result.Add(std::make_shared<ParticleSystemModules::SubEmitters>());
    // if (types & ParticleSystemModules::Types::TextureSheetAnimation) result.Add(std::make_shared<ParticleSystemModules::TextureSheetAnimation>());
    // if (types & ParticleSystemModules::Types::Lights) result.Add(std::make_shared<ParticleSystemModules::Lights>());
    // if (types & ParticleSystemModules::Types::Trails) result.Add(std::make_shared<ParticleSystemModules::Trails>());
    if (types & ParticleSystemModules::Types::Renderer) result.Add(std::make_shared<ParticleSystemModules::Renderer>());

    AddModules(result, true);

    return result;
}

std::shared_ptr<ParticleSystemModules::ModuleBase> ParticleSystem::GetModule(const ParticleSystemModules::Types type)
{
    for (const auto& module : m_Modules)
    {
        if (module->GetType() == type)
            return module;
    }

    return {};
}

List<std::shared_ptr<ParticleSystemModules::ModuleBase>> ParticleSystem::GetModules(const ParticleSystemModules::Types types)
{
    List<std::shared_ptr<ParticleSystemModules::ModuleBase>> result;

    for (const auto& module : m_Modules)
    {
        if (types & module->GetType())
            result.Add(module);
    }

    return result;
}

void ParticleSystem::RemoveModule(const ParticleSystemModules::Types type)
{
    for (size_t i = 0; i < m_Modules.GetSize(); i++)
    {
        if (m_Modules[i]->GetType() != type)
            continue;

        RemoveModule(i);
        return;
    }
}

void ParticleSystem::RemoveModules(const ParticleSystemModules::Types types)
{
    for (size_t i = 0; i < m_Modules.GetSize(); i++)
    {
        if (!(types & m_Modules[i]->GetType()))
            continue;

        RemoveModule(i--);
    }
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

bool_t ParticleSystem::IsComplete()
{
    return !(looping || m_PlaybackTime - startDelay < duration) && GetCurrentParticles() == 0;
}

void ParticleSystem::SetMaxParticles(const uint32_t newMaxParticles)
{
    m_MaxParticles = newMaxParticles;

    // Set up the GPU particle buffer
    // This is done in a very archaic way, but most of the time this won't matter anyway because this function should only be called once per system in a real application
    List<uint8_t> emptyData(GpuParticleStructSize * newMaxParticles);
    for (size_t i = 0; i < emptyData.GetSize(); i += GpuParticleStructSize)
    {
        float_t& lifetime = reinterpret_cast<float_t&>(emptyData[i]);
        lifetime = -std::numeric_limits<float_t>::infinity(); // Set the negative infinity flag for the GPU
    }
    m_ParticleSsbo.SetData(static_cast<int64_t>(GpuParticleStructSize * newMaxParticles), emptyData.GetData(), Graphics::BufferUsage::DynamicCopy);
    emptyData.Resize(0);

    if (m_LiveParticles)
    {
        glUnmapNamedBuffer(m_LiveSsbo.GetId());

        // As we use an immutable buffer to allow buffer mapping,
        // we need to recreate the buffer back each time we want to change its size.
        // Usually this should not happen during gameplay though, so it's not that much of a concern.
        m_LiveSsbo.Recreate();
    }

    const GLsizeiptr aliveSsboSize = static_cast<GLsizeiptr>(sizeof(int32_t) * newMaxParticles);
    m_LiveSsbo.SetStorage(
        aliveSsboSize,
        nullptr,
        Graphics::BufferStorageFlags::MapPersistent | Graphics::BufferStorageFlags::MapRead |
        Graphics::BufferStorageFlags::MapWrite | Graphics::BufferStorageFlags::MapCoherent
    );

    m_LiveParticles = static_cast<int32_t*>(glMapNamedBufferRange(m_LiveSsbo.GetId(), 0, aliveSsboSize, GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT));

    m_UpdateComputeShader->SetUniform("particleCount", newMaxParticles);

    Graphics::MemoryBarrier(Graphics::MemoryBarrierFlags::ShaderStorageBarrier);
}

const List<std::shared_ptr<ParticleSystemModules::ModuleBase>>& ParticleSystem::GetModules() const { return m_Modules; }

void ParticleSystem::Update(const float_t deltaTime)
{
    if (!m_Playing || m_MaxParticles == 0)
        return;

    if (m_PlaybackTime >= startDelay)
    {
        SetComputeShaderUniforms(deltaTime);

        for (const auto& module : m_Modules)
        {
            if (enabledModules & module->GetType())
                module->SetComputeShaderUniforms(*m_UpdateComputeShader);
        }

        const bool_t spawning = looping || m_PlaybackTime - startDelay < duration;

        if (!spawning && GetCurrentParticles() == 0)
            m_Playing = false;

        // Spawn new particles if necessary
        if (spawning)
            SpawnNewParticles();

        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 0, m_LiveSsbo);
        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 1, m_ParticleSsbo);

        m_UpdateComputeShader->Dispatch(m_MaxParticles);

        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 1, 0);
        BindBufferBase(Graphics::BufferType::ShaderStorageBuffer, 0, 0);

        m_SpawnTimer -= deltaTime;
    }

    m_LastPosition = position;
    m_LastPlaybackTime = m_PlaybackTime;

    m_PlaybackTime += deltaTime;

}

void ParticleSystem::SetComputeShaderUniforms(const float_t deltaTime) const
{
    m_UpdateComputeShader->SetUniform("deltaTime", deltaTime);
    m_UpdateComputeShader->SetUniform("time", m_PlaybackTime); // TODO - Maybe multiply by a random seed

    m_UpdateComputeShader->SetUniform("particleLifetime", particleLifetime);
    m_UpdateComputeShader->SetUniform("particleSpeed", particleSpeed);
    m_UpdateComputeShader->SetUniform("particleStartColor", particleStartColor);
    m_UpdateComputeShader->SetUniform("particleStartSize", particleStartSize);

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

    if (!emissionBursts.IsEmpty() && !m_GuiParticleBurstTimeHeld)
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
                break; // Because the list is now sorted by time, instead of continuing, we can just break out of the loop

            if (burst.probability == 0.f)
                continue;

            if (burst.cycles == 0 && burst.interval == 0.f)
                THROW(InvalidOperationException{"A ParticleSystemBurst cannot have both its cycles and interval at 0"});

            const float_t cycles = burst.cycles == 0 ? std::numeric_limits<float_t>::infinity() : static_cast<float_t>(burst.cycles);
            const float_t latestCycleTime = burst.time + (cycles - 1.f) * burst.interval;
            const bool_t timeCondition = latestCycleTime >= m_LastPlaybackTime;

            if (!timeCondition)
                continue;

            const float_t timeOffset = -burst.time + burst.interval;
            const float_t playbackTime = m_PlaybackTime + timeOffset, lastPlaybackTime = m_LastPlaybackTime + timeOffset;
            const bool_t intervalCondition = m_PlaybackTime <= 0.f || burst.interval == 0.f || Calc::OnInterval(playbackTime, lastPlaybackTime, burst.interval);
            if (!intervalCondition)
                continue;

            const int32_t spawnCount = static_cast<int32_t>(std::clamp(
                                           Calc::Round((playbackTime - lastPlaybackTime) / burst.interval),
                                           0.f,
                                           cycles
                                       )) + 1;

            for (int32_t i = 0; i < spawnCount; i++)
            {
                if (burst.probability == 1.f || Random::Instance().Chance(burst.probability))
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

void ParticleSystem::AddModule(const std::shared_ptr<ParticleSystemModules::ModuleBase>& module, const bool_t sort)
{
    m_Modules.Add(module);

    if (sort)
        SortModules();

    if (module->GetType() == ParticleSystemModules::Types::Renderer)
        m_RendererModule = std::reinterpret_pointer_cast<ParticleSystemModules::Renderer>(module);
}

void ParticleSystem::AddModules(const List<std::shared_ptr<ParticleSystemModules::ModuleBase>>& modules, const bool_t sort)
{
    for (const auto& module : modules)
        AddModule(module, false);

    if (sort)
        SortModules();
}

void ParticleSystem::RemoveModule(const size_t index)
{
    if (m_Modules[index]->GetType() == ParticleSystemModules::Types::Renderer)
        m_RendererModule.reset();

    m_Modules.RemoveAt(index);
}

void ParticleSystem::SortModules()
{
    m_Modules.Sort(
        [](const std::shared_ptr<ParticleSystemModules::ModuleBase>& lhs, const std::shared_ptr<ParticleSystemModules::ModuleBase>& rhs)
        {
            return lhs->GetType() < rhs->GetType();
        }
    );
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

uint8_t* ParticleSystem::CreateRawDataCopy()
{
    size_t totalMemory = sizeof(ParticleSystem);

    if (enabledModules & ParticleSystemModules::Types::Shape) totalMemory += sizeof(ParticleSystemModules::Shape);
    if (enabledModules & ParticleSystemModules::Types::VelocityOverLifetime) totalMemory += sizeof(ParticleSystemModules::VelocityOverLifetime);
    // if (enabledModules & ParticleSystemModules::Types::LimitVelocityOverLifetime) totalMemory += sizeof(ParticleSystemModules::LimitVelocityOverLifetime);
    // if (enabledModules & ParticleSystemModules::Types::InheritVelocity) totalMemory += sizeof(ParticleSystemModules::InheritVelocity);
    // if (enabledModules & ParticleSystemModules::Types::LifetimeByEmitterSpeed) totalMemory += sizeof(ParticleSystemModules::LifetimeByEmitterSpeed);
    if (enabledModules & ParticleSystemModules::Types::ForceOverLifetime) totalMemory += sizeof(ParticleSystemModules::ForceOverLifetime);
    if (enabledModules & ParticleSystemModules::Types::ColorOverLifetime) totalMemory += sizeof(ParticleSystemModules::ColorOverLifetime);
    if (enabledModules & ParticleSystemModules::Types::ColorBySpeed) totalMemory += sizeof(ParticleSystemModules::ColorBySpeed);
    // if (enabledModules & ParticleSystemModules::Types::SizeOverLifetime) totalMemory += sizeof(ParticleSystemModules::SizeOverLifetime);
    // if (enabledModules & ParticleSystemModules::Types::SizeBySpeed) totalMemory += sizeof(ParticleSystemModules::SizeBySpeed);
    // if (enabledModules & ParticleSystemModules::Types::RotationOverLifetime) totalMemory += sizeof(ParticleSystemModules::RotationOverLifetime);
    // if (enabledModules & ParticleSystemModules::Types::RotationBySpeed) totalMemory += sizeof(ParticleSystemModules::RotationBySpeed);
    // if (enabledModules & ParticleSystemModules::Types::Noise) totalMemory += sizeof(ParticleSystemModules::Noise);
    // if (enabledModules & ParticleSystemModules::Types::Collision) totalMemory += sizeof(ParticleSystemModules::Collision);
    // if (enabledModules & ParticleSystemModules::Types::SubEmitters) totalMemory += sizeof(ParticleSystemModules::SubEmitters);
    // if (enabledModules & ParticleSystemModules::Types::TextureSheetAnimation) totalMemory += sizeof(ParticleSystemModules::TextureSheetAnimation);
    // if (enabledModules & ParticleSystemModules::Types::Lights) totalMemory += sizeof(ParticleSystemModules::Lights);
    // if (enabledModules & ParticleSystemModules::Types::Trails) totalMemory += sizeof(ParticleSystemModules::Trails);
    if (enabledModules & ParticleSystemModules::Types::Renderer) totalMemory += sizeof(ParticleSystemModules::Renderer);

    uint8_t* dataCopy = static_cast<uint8_t*>(_malloca(totalMemory));
    size_t currentOffset = 0;
    std::memcpy(dataCopy, static_cast<void*>(this), sizeof(ParticleSystem));
    currentOffset += sizeof(ParticleSystem);

    if (enabledModules & ParticleSystemModules::Types::Shape)
    {
        const std::shared_ptr<ParticleSystemModules::Shape> ptr = GetModule<ParticleSystemModules::Shape>();
        std::memcpy(dataCopy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Shape));
        currentOffset += sizeof(ParticleSystemModules::Shape);
    }
    if (enabledModules & ParticleSystemModules::Types::VelocityOverLifetime)
    {
        const std::shared_ptr<ParticleSystemModules::VelocityOverLifetime> ptr = GetModule<ParticleSystemModules::VelocityOverLifetime>();
        std::memcpy(dataCopy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::VelocityOverLifetime));
        currentOffset += sizeof(ParticleSystemModules::VelocityOverLifetime);
    }
    // if (enabledModules & ParticleSystemModules::Types::LimitVelocityOverLifetime)
    //{
    //    const std::shared_ptr<ParticleSystemModules::LimitVelocityOverLifetime> ptr = GetModule<ParticleSystemModules::LimitVelocityOverLifetime>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::LimitVelocityOverLifetime));
    //    currentOffset += sizeof(ParticleSystemModules::LimitVelocityOverLifetime);
    //}
    // if (enabledModules & ParticleSystemModules::Types::InheritVelocity)
    //{
    //    const std::shared_ptr<ParticleSystemModules::InheritVelocity> ptr = GetModule<ParticleSystemModules::InheritVelocity>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::InheritVelocity));
    //    currentOffset += sizeof(ParticleSystemModules::InheritVelocity);
    //}
    // if (enabledModules & ParticleSystemModules::Types::LifetimeByEmitterSpeed)
    //{
    //    const std::shared_ptr<ParticleSystemModules::LifetimeByEmitterSpeed> ptr = GetModule<ParticleSystemModules::LifetimeByEmitterSpeed>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::LifetimeByEmitterSpeed));
    //    currentOffset += sizeof(ParticleSystemModules::LifetimeByEmitterSpeed);
    //}
    if (enabledModules & ParticleSystemModules::Types::ForceOverLifetime)
    {
        const std::shared_ptr<ParticleSystemModules::ForceOverLifetime> ptr = GetModule<ParticleSystemModules::ForceOverLifetime>();
        std::memcpy(dataCopy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::ForceOverLifetime));
        currentOffset += sizeof(ParticleSystemModules::ForceOverLifetime);
    }
    if (enabledModules & ParticleSystemModules::Types::ColorOverLifetime)
    {
        const std::shared_ptr<ParticleSystemModules::ColorOverLifetime> ptr = GetModule<ParticleSystemModules::ColorOverLifetime>();
        std::memcpy(dataCopy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::ColorOverLifetime));
        currentOffset += sizeof(ParticleSystemModules::ColorOverLifetime);
    }
    if (enabledModules & ParticleSystemModules::Types::ColorBySpeed)
    {
        const std::shared_ptr<ParticleSystemModules::ColorBySpeed> ptr = GetModule<ParticleSystemModules::ColorBySpeed>();
        std::memcpy(dataCopy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::ColorBySpeed));
        currentOffset += sizeof(ParticleSystemModules::ColorBySpeed);
    }
    // if (enabledModules & ParticleSystemModules::Types::SizeOverLifetime)
    //{
    //    const std::shared_ptr<ParticleSystemModules::SizeOverLifetime> ptr = GetModule<ParticleSystemModules::SizeOverLifetime>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::SizeOverLifetime));
    //    currentOffset += sizeof(ParticleSystemModules::SizeOverLifetime);
    //}
    // if (enabledModules & ParticleSystemModules::Types::SizeBySpeed)
    //{
    //    const std::shared_ptr<ParticleSystemModules::SizeBySpeed> ptr = GetModule<ParticleSystemModules::SizeBySpeed>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::SizeBySpeed));
    //    currentOffset += sizeof(ParticleSystemModules::SizeBySpeed);
    //}
    // if (enabledModules & ParticleSystemModules::Types::RotationOverLifetime)
    //{
    //    const std::shared_ptr<ParticleSystemModules::RotationOverLifetime> ptr = GetModule<ParticleSystemModules::RotationOverLifetime>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::RotationOverLifetime));
    //    currentOffset += sizeof(ParticleSystemModules::RotationOverLifetime);
    //}
    // if (enabledModules & ParticleSystemModules::Types::RotationBySpeed)
    //{
    //    const std::shared_ptr<ParticleSystemModules::RotationBySpeed> ptr = GetModule<ParticleSystemModules::RotationBySpeed>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::RotationBySpeed));
    //    currentOffset += sizeof(ParticleSystemModules::RotationBySpeed);
    //}
    // if (enabledModules & ParticleSystemModules::Types::Noise)
    //{
    //    const std::shared_ptr<ParticleSystemModules::Noise> ptr = GetModule<ParticleSystemModules::Noise>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Noise));
    //    currentOffset += sizeof(ParticleSystemModules::Noise);
    //}
    // if (enabledModules & ParticleSystemModules::Types::Collision)
    //{
    //    const std::shared_ptr<ParticleSystemModules::Collision> ptr = GetModule<ParticleSystemModules::Collision>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Collision));
    //    currentOffset += sizeof(ParticleSystemModules::Collision);
    //}
    // if (enabledModules & ParticleSystemModules::Types::SubEmitters)
    //{
    //    const std::shared_ptr<ParticleSystemModules::SubEmitters> ptr = GetModule<ParticleSystemModules::SubEmitters>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::SubEmitters));
    //    currentOffset += sizeof(ParticleSystemModules::SubEmitters);
    //}
    // if (enabledModules & ParticleSystemModules::Types::TextureSheetAnimation)
    //{
    //    const std::shared_ptr<ParticleSystemModules::TextureSheetAnimation> ptr = GetModule<ParticleSystemModules::TextureSheetAnimation>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::TextureSheetAnimation));
    //    currentOffset += sizeof(ParticleSystemModules::TextureSheetAnimation);
    //}
    // if (enabledModules & ParticleSystemModules::Types::Lights)
    //{
    //    const std::shared_ptr<ParticleSystemModules::Lights> ptr = GetModule<ParticleSystemModules::Lights>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Lights));
    //    currentOffset += sizeof(ParticleSystemModules::Lights);
    //}
    // if (enabledModules & ParticleSystemModules::Types::Trails)
    //{
    //    const std::shared_ptr<ParticleSystemModules::Trails> ptr = GetModule<ParticleSystemModules::Trails>();
    //    std::memcpy(oldData + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Trails));
    //    currentOffset += sizeof(ParticleSystemModules::Trails);
    //}
    if (enabledModules & ParticleSystemModules::Types::Renderer)
    {
        const std::shared_ptr<ParticleSystemModules::Renderer> ptr = GetModule<ParticleSystemModules::Renderer>();
        std::memcpy(dataCopy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Renderer));
    }

    return dataCopy;
}

// ReSharper disable CppClangTidyBugproneSuspiciousStringCompare
bool_t ParticleSystem::CheckAndDeleteRawDataCopy(uint8_t* copy)
{
    int32_t check = 0;

    size_t currentOffset = 0;
    check |= std::memcmp(copy, static_cast<void*>(this), sizeof(ParticleSystem));
    currentOffset += sizeof(ParticleSystem);

    if (enabledModules & ParticleSystemModules::Types::Shape)
    {
        const std::shared_ptr<ParticleSystemModules::Shape> ptr = GetModule<ParticleSystemModules::Shape>();
        check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Shape));
        currentOffset += sizeof(ParticleSystemModules::Shape);
    }
    if (enabledModules & ParticleSystemModules::Types::VelocityOverLifetime)
    {
        const std::shared_ptr<ParticleSystemModules::VelocityOverLifetime> ptr = GetModule<ParticleSystemModules::VelocityOverLifetime>();
        check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::VelocityOverLifetime));
        currentOffset += sizeof(ParticleSystemModules::VelocityOverLifetime);
    }
    // if (enabledModules & ParticleSystemModules::Types::LimitVelocityOverLifetime)
    //{
    //    const std::shared_ptr<ParticleSystemModules::LimitVelocityOverLifetime> ptr = GetModule<ParticleSystemModules::LimitVelocityOverLifetime>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::LimitVelocityOverLifetime));
    //    currentOffset += sizeof(ParticleSystemModules::LimitVelocityOverLifetime);
    //}
    // if (enabledModules & ParticleSystemModules::Types::InheritVelocity)
    //{
    //    const std::shared_ptr<ParticleSystemModules::InheritVelocity> ptr = GetModule<ParticleSystemModules::InheritVelocity>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::InheritVelocity));
    //    currentOffset += sizeof(ParticleSystemModules::InheritVelocity);
    //}
    // if (enabledModules & ParticleSystemModules::Types::LifetimeByEmitterSpeed)
    //{
    //    const std::shared_ptr<ParticleSystemModules::LifetimeByEmitterSpeed> ptr = GetModule<ParticleSystemModules::LifetimeByEmitterSpeed>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::LifetimeByEmitterSpeed));
    //    currentOffset += sizeof(ParticleSystemModules::LifetimeByEmitterSpeed);
    //}
    if (enabledModules & ParticleSystemModules::Types::ForceOverLifetime)
    {
        const std::shared_ptr<ParticleSystemModules::ForceOverLifetime> ptr = GetModule<ParticleSystemModules::ForceOverLifetime>();
        check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::ForceOverLifetime));
        currentOffset += sizeof(ParticleSystemModules::ForceOverLifetime);
    }
    if (enabledModules & ParticleSystemModules::Types::ColorOverLifetime)
    {
        const std::shared_ptr<ParticleSystemModules::ColorOverLifetime> ptr = GetModule<ParticleSystemModules::ColorOverLifetime>();
        check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::ColorOverLifetime));
        currentOffset += sizeof(ParticleSystemModules::ColorOverLifetime);
    }
    if (enabledModules & ParticleSystemModules::Types::ColorBySpeed)
    {
        const std::shared_ptr<ParticleSystemModules::ColorBySpeed> ptr = GetModule<ParticleSystemModules::ColorBySpeed>();
        check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::ColorBySpeed));
        currentOffset += sizeof(ParticleSystemModules::ColorBySpeed);
    }
    // if (enabledModules & ParticleSystemModules::Types::SizeOverLifetime)
    //{
    //    const std::shared_ptr<ParticleSystemModules::SizeOverLifetime> ptr = GetModule<ParticleSystemModules::SizeOverLifetime>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::SizeOverLifetime));
    //    currentOffset += sizeof(ParticleSystemModules::SizeOverLifetime);
    //}
    // if (enabledModules & ParticleSystemModules::Types::SizeBySpeed)
    //{
    //    const std::shared_ptr<ParticleSystemModules::SizeBySpeed> ptr = GetModule<ParticleSystemModules::SizeBySpeed>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::SizeBySpeed));
    //    currentOffset += sizeof(ParticleSystemModules::SizeBySpeed);
    //}
    // if (enabledModules & ParticleSystemModules::Types::RotationOverLifetime)
    //{
    //    const std::shared_ptr<ParticleSystemModules::RotationOverLifetime> ptr = GetModule<ParticleSystemModules::RotationOverLifetime>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::RotationOverLifetime));
    //    currentOffset += sizeof(ParticleSystemModules::RotationOverLifetime);
    //}
    // if (enabledModules & ParticleSystemModules::Types::RotationBySpeed)
    //{
    //    const std::shared_ptr<ParticleSystemModules::RotationBySpeed> ptr = GetModule<ParticleSystemModules::RotationBySpeed>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::RotationBySpeed));
    //    currentOffset += sizeof(ParticleSystemModules::RotationBySpeed);
    //}
    // if (enabledModules & ParticleSystemModules::Types::Noise)
    //{
    //    const std::shared_ptr<ParticleSystemModules::Noise> ptr = GetModule<ParticleSystemModules::Noise>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Noise));
    //    currentOffset += sizeof(ParticleSystemModules::Noise);
    //}
    // if (enabledModules & ParticleSystemModules::Types::Collision)
    //{
    //    const std::shared_ptr<ParticleSystemModules::Collision> ptr = GetModule<ParticleSystemModules::Collision>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Collision));
    //    currentOffset += sizeof(ParticleSystemModules::Collision);
    //}
    // if (enabledModules & ParticleSystemModules::Types::SubEmitters)
    //{
    //    const std::shared_ptr<ParticleSystemModules::SubEmitters> ptr = GetModule<ParticleSystemModules::SubEmitters>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::SubEmitters));
    //    currentOffset += sizeof(ParticleSystemModules::SubEmitters);
    //}
    // if (enabledModules & ParticleSystemModules::Types::TextureSheetAnimation)
    //{
    //    const std::shared_ptr<ParticleSystemModules::TextureSheetAnimation> ptr = GetModule<ParticleSystemModules::TextureSheetAnimation>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::TextureSheetAnimation));
    //    currentOffset += sizeof(ParticleSystemModules::TextureSheetAnimation);
    //}
    // if (enabledModules & ParticleSystemModules::Types::Lights)
    //{
    //    const std::shared_ptr<ParticleSystemModules::Lights> ptr = GetModule<ParticleSystemModules::Lights>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Lights));
    //    currentOffset += sizeof(ParticleSystemModules::Lights);
    //}
    // if (enabledModules & ParticleSystemModules::Types::Trails)
    //{
    //    const std::shared_ptr<ParticleSystemModules::Trails> ptr = GetModule<ParticleSystemModules::Trails>();
    //    check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Trails));
    //    currentOffset += sizeof(ParticleSystemModules::Trails);
    //}
    if (enabledModules & ParticleSystemModules::Types::Renderer)
    {
        const std::shared_ptr<ParticleSystemModules::Renderer> ptr = GetModule<ParticleSystemModules::Renderer>();
        check |= std::memcmp(copy + currentOffset, static_cast<void*>(ptr.get()), sizeof(ParticleSystemModules::Renderer));
    }

    _freea(copy);

    return check != 0;
}
// ReSharper enable CppClangTidyBugproneSuspiciousStringCompare
