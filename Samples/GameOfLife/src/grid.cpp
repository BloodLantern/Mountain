#include "grid.hpp"

#include <stdexcept>

#include "Mountain/rendering/draw.hpp"

Grid::~Grid()
{
    delete m_Blocks;
}

void Grid::Update()
{
    // Make sure the empty block is still empty
    if (!m_Empty.GetEmpty())
        m_Empty = Block{};

    for (uint64_t y = 0; y < m_Height; y++)
    {
        for (uint64_t x = 0; x < m_Width; x++)
        {
            Block& block = GetBlock(x, y);

            if (block.GetEmpty())
                continue;
        }
    }
}

void Grid::Render(const float_t cellSize)
{
    constexpr float_t blockSize = BlockSize;

    for (uint64_t y = 0; y < m_Height; y++)
    {
        for (uint64_t x = 0; x < m_Width; x++)
        {
            Block& block = GetBlock(x, y);
            block.Render(
                {
                    static_cast<float_t>(x) * cellSize * blockSize,
                    static_cast<float_t>(y) * cellSize * blockSize
                },
                cellSize
            );
        }
    }
}

uint64_t Grid::GetWidth() const
{
    return m_Width;
}

uint64_t Grid::GetHeight() const
{
    return m_Height;
}

void Grid::SetSize(const uint64_t newWidth, const uint64_t newHeight)
{
    delete m_Blocks;
    m_Blocks = new Block[newHeight * newWidth];

    m_Width = newWidth;
    m_Height = newHeight;
}

Block& Grid::GetBlock(const uint64_t x, const uint64_t y)
{
    if (x >= m_Width || y >= m_Height)
        return m_Empty;

    return m_Blocks[y * m_Width + x];
}

bool_t Grid::GetCell(const uint64_t blockX, const uint64_t blockY, const uint8_t cellX, const uint8_t cellY)
{
    return GetBlock(blockX, blockY).GetCell(cellX, cellY);
}

void Grid::SetCell(const uint64_t blockX, const uint64_t blockY, const uint8_t cellX, const uint8_t cellY, const bool_t value)
{
    GetBlock(blockX, blockY).SetCell(cellX, cellY, value);
}

void Grid::ToggleCell(const uint64_t blockX, const uint64_t blockY, const uint8_t cellX, const uint8_t cellY)
{
    GetBlock(blockX, blockY).ToggleCell(cellX, cellY);
}
