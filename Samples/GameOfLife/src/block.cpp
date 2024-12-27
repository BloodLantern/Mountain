#include "block.hpp"

#include <stdexcept>

#include "Maths/vector2.hpp"
#include "Mountain/rendering/draw.hpp"

#define CHECK_RANGE(x, y)                                                                                   \
    if ((x) >= BlockSize || (y) >= BlockSize)                                                               \
        throw std::invalid_argument{ "Cannot get/set cell with x or y greater than BlockSize in Block" }

Block::Block()
{
    for (BlockType& line : m_Lines)
        line = 0;
}

void Block::Render(const Vector2 offset) const
{
    for (uint8_t y = 0; y < BlockSize; y++)
    {
        for (uint8_t x = 0; x < BlockSize; x++)
        {
            const bool_t cell = GetCell(x, y);
            if (!cell) // No need to draw the cell if it's dead
                continue;

            Mountain::Draw::RectangleFilled(
                offset + Vector2{ static_cast<float_t>(x), static_cast<float_t>(y) },
                Vector2::One()
            );
        }
    }
}

bool_t Block::GetCell(const uint8_t x, const uint8_t y) const
{
    CHECK_RANGE(x, y);

    const BlockType bit = 1ull << x;
    return m_Lines[y] & bit;
}

void Block::SetCell(const uint8_t x, const uint8_t y, const bool_t value)
{
    CHECK_RANGE(x, y);

    BlockType& line = m_Lines[y];
    const BlockType bit = 1ull << x;
    if (value)
        line |= bit;
    else
        line &= ~bit;

    if (value)
        m_Empty = false;
    else
        UpdateEmptyState();
}

void Block::ToggleCell(const uint8_t x, const uint8_t y)
{
    CHECK_RANGE(x, y);

    BlockType& line = m_Lines[y];
    const BlockType bit = 1ull << x;

    const bool_t oldValue = line & bit;

    line ^= bit;

    if (!oldValue)
        m_Empty = false;
    else
        UpdateEmptyState();
}

void Block::UpdateEmptyState()
{
    for (const BlockType line : m_Lines)
    {
        if (line)
        {
            m_Empty = false;
            return;
        }
    }
    m_Empty = true;
}

bool_t Block::GetEmpty() const
{
    return m_Empty;
}
