#pragma once

#include "Audio.hpp"
#include "Buffer.hpp"
#include "Mountain/Core.hpp"

namespace Mountain
{
    class Sound;
}

namespace Mountain::Audio
{
    /// @brief Represents an audio source
    class MOUNTAIN_API Source
    {
    public:
        struct MOUNTAIN_API SourceInfo
        {
            constexpr SourceInfo() = default;
            constexpr SourceInfo(const float_t vol, const Vector2& pos)
                : volume(vol), position(pos) {}
            constexpr SourceInfo(const float_t vol, const Vector2& pos, const Vector2& vel, const float_t p)
                : volume(vol), position(pos), velocity(vel), pitch(p) {}
            
            /// @brief Volume in the range [0, inf]. Default value is 1.
            float_t volume = 1.f;
            Vector2 position;
            Vector2 velocity;
            /// @brief Pitch in the range [0, inf]. Default value is 1.
            float_t pitch = 1.f;
        };
        
        explicit Source();
        explicit Source(const SourceInfo& info);

        ~Source();

        DELETE_COPY_MOVE_OPERATIONS(Source)

        void Start() const;
        void Pause() const;
        void Stop() const;

        void SetVolume(float_t volume);
        void SetPitch(float_t pitch);

        /// @brief Updates the position of the source
        /// @param position Position
        /// @param updateVelocity If true, the velocity will automatically be updated based on the old and new position
        void SetPosition(Vector2 position, bool_t updateVelocity = false);
        void SetVelocity(Vector2 velocity);

        void SetInfo(const SourceInfo& info);

        void SetUnstreamedBuffer(Buffer* buffer) const;

        void SetLooping(bool_t looping) const;

        ATTRIBUTE_NODISCARD
        SourceState GetState() const;

        ATTRIBUTE_NODISCARD
        const SourceInfo& GetInfo() const;

    private:
        void ApplyInfo();

        uint32_t m_Handle = 0;

        SourceInfo m_Info;
    };
}
