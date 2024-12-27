#include "grid.hpp"

#include <stdexcept>

#include "Mountain/rendering/draw.hpp"
#include "Mountain/rendering/renderer.hpp"

Grid::~Grid()
{
    delete m_Blocks;
}

void Grid::Update()
{
    // Make sure the empty block is still empty
    if (!m_Empty.GetEmpty())
        m_Empty = Block{};

    for (uint64_t y = 0; y < m_Height * BlockSize; y++)
    {
        for (uint64_t x = 0; x < m_Width * BlockSize; x++)
        {
            const uint64_t blockX = x / BlockSize, blockY = y / BlockSize;
            Block& block = GetBlock(blockX, blockY);

            const uint8_t cellX = x % BlockSize, cellY = y % BlockSize;

            /*if (block.GetEmpty())
                continue;*/

            const bool_t cell = block.GetCell(cellX, cellY);

            uint8_t liveNeighborCells = 0;

            for (int8_t offsetY = -1; offsetY <= 1; offsetY++)
            {
                for (int8_t offsetX = -1; offsetX <= 1; offsetX++)
                {
                    if (offsetX == 0 && offsetY == 0)
                        continue;

                    uint64_t offsetBlockX = blockX;
                    uint8_t offsetCellX = static_cast<uint8_t>(cellX + offsetX);
                    if (offsetCellX == 0xFF) // Underflow
                    {
                        if (blockX == 0)
                            offsetBlockX = m_Width - 1;
                        else
                            offsetBlockX--;
                        offsetCellX = BlockSize - 1;
                    }
                    else if (offsetCellX == BlockSize)
                    {
                        if (blockX == m_Width - 1)
                            offsetBlockX = 0;
                        else
                            offsetBlockX++;
                        offsetCellX = 0;
                    }

                    uint64_t offsetBlockY = blockY;
                    uint8_t offsetCellY = static_cast<uint8_t>(cellY + offsetY);
                    if (offsetCellY == 0xFF) // Underflow
                    {
                        if (blockY == 0)
                            offsetBlockY = m_Height - 1;
                        else
                            offsetBlockY--;
                        offsetCellY = BlockSize - 1;
                    }
                    else if (offsetCellY == BlockSize)
                    {
                        if (blockY == m_Height - 1)
                            offsetBlockY = 0;
                        else
                            offsetBlockY++;
                        offsetCellY = 0;
                    }

                    if (GetCell(offsetBlockX, offsetBlockY, offsetCellX, offsetCellY))
                    {
                        liveNeighborCells++;

                        if (cell && liveNeighborCells > 3)
                        {
                            goto out;
                        }
                    }
                }
            }
            out:

            if (cell)
            {
                if (liveNeighborCells < 2 || liveNeighborCells > 3)
                    block.SetCell(cellX, cellY, false);
            }
            else
            {
                if (liveNeighborCells == 3)
                    block.SetCell(cellX, cellY, true);
            }
        }
    }
}

void Grid::PreRenderGrid()
{
    if (m_RenderTarget.GetInitialized())
        m_RenderTarget.Reset();

    m_RenderTarget.Initialize(
        {
            static_cast<int32_t>(m_Width * BlockSize * static_cast<int32_t>(GridPreRenderGridFactor)),
            static_cast<int32_t>(m_Height * BlockSize * static_cast<int32_t>(GridPreRenderGridFactor))
        },
        Mountain::Graphics::MagnificationFilter::Nearest
    );

    Mountain::Renderer::PushRenderTarget(m_RenderTarget);

    for (uint64_t y = 1; y < m_Height * BlockSize; y++)
    {
        Mountain::Draw::Line(
            { 0.f, static_cast<float_t>(y) * GridPreRenderGridFactor },
            { static_cast<float_t>(m_Width * BlockSize) * GridPreRenderGridFactor, static_cast<float_t>(y) * GridPreRenderGridFactor },
            Mountain::Color{ 0.2f }
        );
    }
    for (uint64_t x = 1; x < m_Width * BlockSize; x++)
    {
        Mountain::Draw::Line(
            { static_cast<float_t>(x) * GridPreRenderGridFactor, 0.f },
            { static_cast<float_t>(x) * GridPreRenderGridFactor, static_cast<float_t>(m_Height * BlockSize) * GridPreRenderGridFactor },
            Mountain::Color{ 0.2f }
        );
    }

    for (uint64_t y = 1; y < m_Height; y++)
    {
        Mountain::Draw::Line(
            { 0.f, static_cast<float_t>(y * BlockSize) * GridPreRenderGridFactor },
            { static_cast<float_t>(m_Width * BlockSize) * GridPreRenderGridFactor, static_cast<float_t>(y * BlockSize) * GridPreRenderGridFactor },
            Mountain::Color{ 0.5f }
        );
    }
    for (uint64_t x = 1; x < m_Width; x++)
    {
        Mountain::Draw::Line(
            { static_cast<float_t>(x * BlockSize) * GridPreRenderGridFactor, 0.f },
            { static_cast<float_t>(x * BlockSize) * GridPreRenderGridFactor, static_cast<float_t>(m_Height * BlockSize) * GridPreRenderGridFactor },
            Mountain::Color{ 0.5f }
        );
    }

    Mountain::Renderer::PopRenderTarget();
}

void Grid::Render()
{
    constexpr float_t blockSize = BlockSize;

    for (uint64_t y = 0; y < m_Height; y++)
    {
        for (uint64_t x = 0; x < m_Width; x++)
        {
            Block& block = GetBlock(x, y);
            block.Render(
                {
                    static_cast<float_t>(x) * blockSize,
                    static_cast<float_t>(y) * blockSize
                }
            );
        }
    }

    Mountain::Draw::RenderTarget(m_RenderTarget, Vector2::Zero(), Vector2::One() / GridPreRenderGridFactor);
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
