#pragma once

#include "Maths/vector2.hpp"
#include "Mountain/core.hpp"

using BlockType = uint64_t;
constexpr uint8_t BlockSize = sizeof(BlockType) * 8;

// 64x64 cell block
class Block
{
public:
    Block();

    void Render(Vector2 offset, float_t cellSize) const;

    [[nodiscard]]
    bool_t GetCell(uint8_t x, uint8_t y) const;
    void SetCell(uint8_t x, uint8_t y, bool_t value);
    void ToggleCell(uint8_t x, uint8_t y);

    [[nodiscard]]
    bool_t GetEmpty() const;

private:
    BlockType m_Lines[BlockSize];

    bool_t m_Empty = true;
};
