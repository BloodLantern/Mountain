#pragma once

BEGIN_MOUNTAIN

constexpr Rectangle Hitbox::ToRectangle() const { return { position, size }; }

END_MOUNTAIN
