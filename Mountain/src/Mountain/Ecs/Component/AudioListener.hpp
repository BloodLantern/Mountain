#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector3.hpp>

#include "Mountain/Ecs/Component/Component.hpp"

namespace Mountain
{
    class MOUNTAIN_API AudioListener : public Component
    {
    public:
        bool dopplerEffect = false;

        void Update() override;

        /// @brief Get the volume in the range [0, inf].
        ATTRIBUTE_NODISCARD
        f32 GetVolume() const;

        /// @brief Set the volume in the range [0, inf]. Default value is 1.
        void SetVolume(f32 newVolume);

    private:
        /// @brief Volume in the range [0, inf]. Default value is 1.
        f32 m_Volume = 1.f;

        Vector2 m_LastPosition;
    };
}
