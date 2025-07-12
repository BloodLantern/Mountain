#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Audio/Listener.hpp"

#include "Mountain/Ecs/Component/Component.hpp"

namespace Mountain
{
    class MOUNTAIN_API AudioListener : public Component
    {
    public:
        bool_t dopplerEffect = false;

        void Update() override;

        /// @brief Get the volume in the range [0, inf].
        ATTRIBUTE_NODISCARD
        float_t GetVolume() const;

        /// @brief Set the volume in the range [0, inf]. Default value is 1.
        void SetVolume(float_t newVolume);

    private:
        Audio::Listener m_Listener;
    };
}
