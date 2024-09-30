#pragma once

#include "Mountain/core.hpp"

#include "Mountain/scene/component/component.hpp"
#include "Mountain/utils/color.hpp"

BEGIN_MOUNTAIN

class LightSource : public Component
{
public:
    Color color = Color::White();
    float_t intensity = 0.f;
    float_t radius = 0.f;
    float_t angleMin = 0.f;
    float_t angleMax = Calc::TwoPi;
    
    Vector2 offset;

    MOUNTAIN_API void Update() override;

    [[nodiscard]]
    MOUNTAIN_API Vector2 GetPosition() const;

private:
    Vector2 m_Position;
};

END_MOUNTAIN
