#pragma once

BEGIN_MOUNTAIN

template <size_t Size>
void Draw::Points(const std::array<Vector2, Size>& positions, const Color& color)
{
    Points(positions.data(), static_cast<uint32_t>(positions.size()), color);
}

template <size_t Size>
void Draw::Points(const std::array<Vector2, Size>& positions, const std::array<Color, Size>& colors)
{
    Points(positions.data(), colors.data(), static_cast<uint32_t>(positions.size()));
}

END_MOUNTAIN
