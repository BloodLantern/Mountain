#pragma once

#include "core.hpp"

#include <Maths/vector3.hpp>

#include "scene/component.hpp"

BEGIN_MOUNTAIN

class MOUNTAIN_API AudioListener : public Component
{
public:
    bool_t dopplerEffect = true;
    
    void Update() override;
    
    /// @brief Get the volume in the range [0, inf].
    [[nodiscard]]
    float_t GetVolume() const;
    
    /// @brief Set the volume in the range [0, inf]. Default value is 1.
    void SetVolume(float_t newVolume);

private:
    /// @brief Volume in the range [0, inf]. Default value is 1.
    float_t m_Volume = 1.f;

    Vector2 m_LastPosition;
};

END_MOUNTAIN
