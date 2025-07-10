#pragma once

#include <Math/vector2.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Rendering/GpuBuffer.hpp"
#include "Mountain/Rendering/GpuVertexArray.hpp"
#include "Mountain/Rendering/ParticleSystemModules.hpp"
#include "Mountain/Resource/ComputeShader.hpp"
#include "Mountain/Resource/Shader.hpp"
#include "Mountain/Utils/Color.hpp"
#include "Mountain/Containers/List.hpp"

// OpenGL type forward declaration
// ReSharper disable once CppInconsistentNaming
struct __GLsync;  // NOLINT(clang-diagnostic-reserved-identifier, bugprone-reserved-identifier)

namespace Mountain
{
    struct ParticleSystemBurst
    {
        /// @brief The time at which the burst should occur
        float_t time = 0.f;
        /// @brief The number of particles to spawn in the burst
        uint32_t count = 30;
        /// @brief How many times the burst should repeat
        uint32_t cycles = 1;
        /// @brief The time interval between each burst cycle
        float_t interval = 0.01f;
        /// @brief The probability for the burst to happen
        float_t probability = 1.f;
    };

    class ParticleSystem
    {
    public:
        // Particle system settings

        Vector2 position;
        float_t rotation;
        float_t duration = 5.f;
        bool_t looping = true;
        float_t startDelay;
        bool_t useUnscaledDeltaTime = false;

        // Emission settings

        float_t emissionRateOverTime = 10.f;
        float_t emissionRateOverDistance = 0.f;
        List<ParticleSystemBurst> emissionBursts;

        // Particle settings

        float_t particleLifetime = 5.f;
        float_t particleSpeed = 5.f;
        Color particleStartColor = Color::White();

        // Modules

        List<std::shared_ptr<ParticleSystemModules::ModuleBase>> modules;
        ParticleSystemModules::Types enabledModules = ParticleSystemModules::Types::Default;

        MOUNTAIN_API ParticleSystem() = default;
        MOUNTAIN_API explicit ParticleSystem(uint32_t maxParticles);
        MOUNTAIN_API virtual ~ParticleSystem();

        DEFAULT_COPY_MOVE_OPERATIONS(ParticleSystem)

        MOUNTAIN_API void Update();
        MOUNTAIN_API void Render();
        MOUNTAIN_API void RenderImGui();
        MOUNTAIN_API void RenderDebug();

        MOUNTAIN_API void TogglePlay();
        MOUNTAIN_API void Restart();
        MOUNTAIN_API void Stop();

        /// @brief Get the current living particle count.
        /// @details This can vary a lot from frame to frame because we count the particles on the CPU from the GPU memory.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API uint32_t GetCurrentParticles();

        /// @brief Get whether the system has finished playing.
        /// @details E.g., whether it is not spawning particles anymore and @code GetCurrentParticles() == 0@endcode.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t IsComplete();

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API uint32_t GetMaxParticles() const;
        /// @brief Set the new maximum particle count
        /// @warning This is a very heavy operation, avoid doing this each frame
        MOUNTAIN_API void SetMaxParticles(uint32_t newMaxParticles);

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t IsPlaying() const;

    private:
        uint32_t m_MaxParticles = 0;
        int32_t* m_LiveParticles = nullptr;
        __GLsync* m_SyncObject = nullptr;

        float_t m_PlaybackTime = 0.f; // System lifetime
        float_t m_LastPlaybackTime = 0.f;
        double_t m_SpawnTimer = 0.0;
        bool_t m_Playing = true;
        Vector2 m_LastPosition;

        Pointer<ComputeShader> m_UpdateComputeShader;

        Pointer<Shader> m_DrawShader;
        Graphics::GpuBuffer m_LiveSsbo, m_ParticleSsbo;
        Graphics::GpuVertexArray m_DrawVao;

        bool_t m_GuiParticleBurstTimeHeld = false;
        Vector2 m_RenderTargetSize;

        void SetComputeShaderUniforms(float_t deltaTime) const;
        void SpawnNewParticles();

        /// @brief Wait for the GPU buffer to sync with the CPU. After that call, the CPU can read/write to that buffer.
        static void WaitBufferSync(__GLsync* syncObject);
        /// @brief Lock the buffer to GPU read/write-only. After that call, the CPU cannot access that buffer anymore.
        static void LockBuffer(__GLsync*& syncObject);
    };
}
