#pragma once

BEGIN_MOUNTAIN

constexpr Rectangle Hitbox::ToRectangle() const { return { GetActualPosition(), size }; }

END_MOUNTAIN
