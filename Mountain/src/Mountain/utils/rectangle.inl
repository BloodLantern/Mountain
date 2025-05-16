#pragma once

namespace Mountain
{
    constexpr Rectangle::Rectangle(const Vector2 size): size(size) {}

    constexpr Rectangle::Rectangle(const Vector2 position, const Vector2 size) : position(position), size(size) {}

    constexpr float Rectangle::Left() const { return position.x; }

    constexpr float Rectangle::Right() const { return position.x + size.x; }

    constexpr float Rectangle::Top() const { return position.y; }

    constexpr float Rectangle::Bottom() const { return position.y + size.y; }

    constexpr Vector2 Rectangle::Center() const { return position + size / 2; }

    constexpr Vector2 Rectangle::TopLeft() const { return position; }

    constexpr Vector2 Rectangle::TopRight() const { return position + Vector2(size.x, 0.f); }

    constexpr Vector2 Rectangle::BottomLeft() const { return position + Vector2(0.f, size.y); }

    constexpr Vector2 Rectangle::BottomRight() const { return position + size; }

    constexpr float Rectangle::Width() const { return size.x; }

    constexpr float Rectangle::Height() const { return size.y; }
}
