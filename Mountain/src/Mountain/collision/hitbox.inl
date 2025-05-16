#pragma once

namespace Mountain
{
    constexpr Rectangle Hitbox::ToRectangle() const { return { GetActualPosition(), size }; }
}
