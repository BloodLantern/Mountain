#pragma once

#include <Math/vector2.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Rendering/GpuBuffer.hpp"
#include "Mountain/Rendering/GpuVertexArray.hpp"
#include "Mountain/Rendering/ParticleSystemModules.hpp"
#include "Mountain/Resource/ComputeShader.hpp"
#include "Mountain/Resource/Shader.hpp"
#include "Mountain/Utils/Color.hpp"

// OpenGL type forward declaration
// ReSharper disable once CppInconsistentNaming
struct __GLsync;  // NOLINT(clang-diagnostic-reserved-identifier, bugprone-reserved-identifier)

// TODO - Add settings for negating the delta time when reaching the end of the system lifetime

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

        /// @brief The number of particles to spawn each second
        float_t emissionRateOverTime = 10.f;
        /// @brief The number of particles to spawn for every pixel traveled by the system
        float_t emissionRateOverDistance = 0.f;
        /// @brief Bursts of particles to spawn
        List<ParticleSystemBurst> emissionBursts;

        // Particle settings

        float_t particleLifetime = 5.f;
        float_t particleSpeed = 5.f;
        Color particleStartColor = Color::White();
        float_t particleStartSize = 1.f;

        // Modules

        ParticleSystemModules::Types enabledModules = ParticleSystemModules::Types::Default;

        /// @brief Constructs a ParticleSystem with 1000 max particles
        /// @remark This simply calls @c ParticleSystem(uint32_t) with @c 1000 as a parameter
        MOUNTAIN_API ParticleSystem();
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

        MOUNTAIN_API std::shared_ptr<ParticleSystemModules::ModuleBase> AddModule(ParticleSystemModules::Types type);
        MOUNTAIN_API List<std::shared_ptr<ParticleSystemModules::ModuleBase>> AddModules(ParticleSystemModules::Types types);
        MOUNTAIN_API std::shared_ptr<ParticleSystemModules::ModuleBase> GetModule(ParticleSystemModules::Types type);
        MOUNTAIN_API List<std::shared_ptr<ParticleSystemModules::ModuleBase>> GetModules(ParticleSystemModules::Types types);
        MOUNTAIN_API void RemoveModule(ParticleSystemModules::Types type);
        MOUNTAIN_API void RemoveModules(ParticleSystemModules::Types types);

        template <Concepts::ParticleSystemModule ModuleT>
        std::shared_ptr<ModuleT> AddModule();
        template <Concepts::ParticleSystemModule ModuleT>
        std::shared_ptr<ModuleT> GetModule();
        template <Concepts::ParticleSystemModule ModuleT>
        void RemoveModule();

        /// @brief Get the current living particle count.
        /// @details This can vary a lot from frame to frame because we count the particles on the CPU from the GPU memory.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API uint32_t GetCurrentParticles();

        /// @brief Get whether the system has finished playing.
        /// @details E.g., whether it is not spawning particles anymore and @code GetCurrentParticles() == 0@endcode.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t IsComplete();

        GETTER(uint32_t, MaxParticles, m_MaxParticles)
        /// @brief Set the new maximum particle count
        /// @warning This can be a quite heavy operation depending on the requested new max particle, avoid doing this every frame
        MOUNTAIN_API void SetMaxParticles(uint32_t newMaxParticles);

        GETTER(bool_t, Playing, m_Playing)
        GETTER(const List<std::shared_ptr<ParticleSystemModules::ModuleBase>>&, Modules, m_Modules)

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

        bool_t m_GuiParticleBurstTimeHeld = false;
        Vector2 m_RenderTargetSize;

        List<std::shared_ptr<ParticleSystemModules::ModuleBase>> m_Modules;

        std::shared_ptr<ParticleSystemModules::Renderer> m_RendererModule;

        bool_t m_LastUseTexture = false;

        MOUNTAIN_API void Update(float_t deltaTime);

        MOUNTAIN_API void SetComputeShaderUniforms(float_t deltaTime) const;
        MOUNTAIN_API void SpawnNewParticles();

        MOUNTAIN_API void AddModule(const std::shared_ptr<ParticleSystemModules::ModuleBase>& module, bool_t sort);
        MOUNTAIN_API void AddModules(const List<std::shared_ptr<ParticleSystemModules::ModuleBase>>& modules, bool_t sort);
        MOUNTAIN_API void RemoveModule(size_t index);

        MOUNTAIN_API void SortModules();

        /// @brief Wait for the GPU buffer to sync with the CPU. After that call, the CPU can read/write to that buffer.
        MOUNTAIN_API static void WaitBufferSync(__GLsync* syncObject);
        /// @brief Lock the buffer to GPU read/write-only. After that call, the CPU cannot access that buffer anymore.
        MOUNTAIN_API static void LockBuffer(__GLsync*& syncObject);

        MOUNTAIN_API uint8_t* CreateRawDataCopy();
        MOUNTAIN_API bool_t CheckAndDeleteRawDataCopy(uint8_t* copy);
    };

    template <Concepts::ParticleSystemModule ModuleT>
    std::shared_ptr<ModuleT> ParticleSystem::AddModule()
    {
        std::shared_ptr<ModuleT> result;

        if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Shape>) result = std::make_shared<ParticleSystemModules::Shape>();
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::VelocityOverLifetime>) result = std::make_shared<ParticleSystemModules::VelocityOverLifetime>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::LimitVelocityOverLifetime>) result = std::make_shared<ParticleSystemModules::LimitVelocityOverLifetime>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::InheritVelocity>) result = std::make_shared<ParticleSystemModules::InheritVelocity>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::LifetimeByEmitterSpeed>) result = std::make_shared<ParticleSystemModules::LifetimeByEmitterSpeed>();
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ForceOverLifetime>) result = std::make_shared<ParticleSystemModules::ForceOverLifetime>();
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ColorOverLifetime>) result = std::make_shared<ParticleSystemModules::ColorOverLifetime>();
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ColorBySpeed>) result = std::make_shared<ParticleSystemModules::ColorBySpeed>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SizeOverLifetime>) result = std::make_shared<ParticleSystemModules::SizeOverLifetime>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SizeBySpeed>) result = std::make_shared<ParticleSystemModules::SizeBySpeed>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::RotationOverLifetime>) result = std::make_shared<ParticleSystemModules::RotationOverLifetime>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::RotationBySpeed>) result = std::make_shared<ParticleSystemModules::RotationBySpeed>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Noise>) result = std::make_shared<ParticleSystemModules::Noise>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Collision>) result = std::make_shared<ParticleSystemModules::Collision>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SubEmitters>) result = std::make_shared<ParticleSystemModules::SubEmitter>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::TextureSheetAnimation>) result = std::make_shared<ParticleSystemModules::TextureSheetAnimation>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Lights>) result = std::make_shared<ParticleSystemModules::Light>();
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Trails>) result = std::make_shared<ParticleSystemModules::Trail>();
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Renderer>) result = std::make_shared<ParticleSystemModules::Renderer>();
        else static_assert(false, "Invalid module type");

        AddModule(std::reinterpret_pointer_cast<ParticleSystemModules::ModuleBase>(result), true);

        return result;
    }

    template <Concepts::ParticleSystemModule ModuleT>
    // ReSharper disable once CppNotAllPathsReturnValue
    std::shared_ptr<ModuleT> ParticleSystem::GetModule()
    {
        if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Shape>)
            return std::reinterpret_pointer_cast<ParticleSystemModules::Shape>(GetModule(ParticleSystemModules::Types::Shape));
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::VelocityOverLifetime>)
            return std::reinterpret_pointer_cast<ParticleSystemModules::VelocityOverLifetime>(GetModule(ParticleSystemModules::Types::VelocityOverLifetime));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::LimitVelocityOverLifetime>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::LimitVelocityOverLifetime>(GetModule(ParticleSystemModules::Types::LimitVelocityOverLifetime));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::InheritVelocity>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::InheritVelocity>(GetModule(ParticleSystemModules::Types::InheritVelocity));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::LifetimeByEmitterSpeed>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::LifetimeByEmitterSpeed>(GetModule(ParticleSystemModules::Types::LifetimeByEmitterSpeed));
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ForceOverLifetime>)
            return std::reinterpret_pointer_cast<ParticleSystemModules::ForceOverLifetime>(GetModule(ParticleSystemModules::Types::ForceOverLifetime));
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ColorOverLifetime>)
            return std::reinterpret_pointer_cast<ParticleSystemModules::ColorOverLifetime>(GetModule(ParticleSystemModules::Types::ColorOverLifetime));
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ColorBySpeed>)
            return std::reinterpret_pointer_cast<ParticleSystemModules::ColorBySpeed>(GetModule(ParticleSystemModules::Types::ColorBySpeed));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SizeOverLifetime>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::SizeOverLifetime>(GetModule(ParticleSystemModules::Types::SizeOverLifetime));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SizeBySpeed>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::SizeBySpeed>(GetModule(ParticleSystemModules::Types::SizeBySpeed));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::RotationOverLifetime>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::RotationOverLifetime>(GetModule(ParticleSystemModules::Types::RotationOverLifetime));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::RotationBySpeed>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::RotationBySpeed>(GetModule(ParticleSystemModules::Types::RotationBySpeed));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Noise>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::Noise>(GetModule(ParticleSystemModules::Types::Noise));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Collision>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::Collision>(GetModule(ParticleSystemModules::Types::Collision));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SubEmitters>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::SubEmitters>(GetModule(ParticleSystemModules::Types::SubEmitters));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::TextureSheetAnimation>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::TextureSheetAnimation>(GetModule(ParticleSystemModules::Types::TextureSheetAnimation));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Lights>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::Lights>(GetModule(ParticleSystemModules::Types::Lights));
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Trails>)
        //     return std::reinterpret_pointer_cast<ParticleSystemModules::Trails>(GetModule(ParticleSystemModules::Types::Trails));
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Renderer>)
            return std::reinterpret_pointer_cast<ParticleSystemModules::Renderer>(GetModule(ParticleSystemModules::Types::Renderer));
        else
            static_assert(false, "Invalid module type");
    }

    template <Concepts::ParticleSystemModule ModuleT>
    void ParticleSystem::RemoveModule()
    {
        if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Shape>) RemoveModule(ParticleSystemModules::Types::Shape);
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::VelocityOverLifetime>) RemoveModule(ParticleSystemModules::Types::VelocityOverLifetime);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::LimitVelocityOverLifetime>) RemoveModule(ParticleSystemModules::Types::LimitVelocityOverLifetime);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::InheritVelocity>) RemoveModule(ParticleSystemModules::Types::InheritVelocity);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::LifetimeByEmitterSpeed>) RemoveModule(ParticleSystemModules::Types::LifetimeByEmitterSpeed);
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ForceOverLifetime>) RemoveModule(ParticleSystemModules::Types::ForceOverLifetime);
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ColorOverLifetime>) RemoveModule(ParticleSystemModules::Types::ColorOverLifetime);
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::ColorBySpeed>) RemoveModule(ParticleSystemModules::Types::ColorBySpeed);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SizeOverLifetime>) RemoveModule(ParticleSystemModules::Types::SizeOverLifetime);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SizeBySpeed>) RemoveModule(ParticleSystemModules::Types::SizeBySpeed);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::RotationOverLifetime>) RemoveModule(ParticleSystemModules::Types::RotationOverLifetime);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::RotationBySpeed>) RemoveModule(ParticleSystemModules::Types::RotationBySpeed);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Noise>) RemoveModule(ParticleSystemModules::Types::Noise);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Collision>) RemoveModule(ParticleSystemModules::Types::Collision);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::SubEmitters>) RemoveModule(ParticleSystemModules::Types::SubEmitters);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::TextureSheetAnimation>) RemoveModule(ParticleSystemModules::Types::TextureSheetAnimation);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Lights>) RemoveModule(ParticleSystemModules::Types::Lights);
        // else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Trails>) RemoveModule(ParticleSystemModules::Types::Trails);
        else if constexpr (Meta::IsSame<ModuleT, ParticleSystemModules::Renderer>) RemoveModule(ParticleSystemModules::Types::Renderer);
        else static_assert(false, "Invalid module type");
    }
}
