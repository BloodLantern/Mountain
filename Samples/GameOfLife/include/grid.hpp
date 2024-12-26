#pragma once

#include "block.hpp"

class Grid
{
public:
    Grid() = default;
    ~Grid();

    DELETE_COPY_MOVE_OPERATIONS(Grid)

    void Update();
    void Render(float_t cellSize);

    [[nodiscard]]
    uint64_t GetWidth() const;
    [[nodiscard]]
    uint64_t GetHeight() const;
    void SetSize(uint64_t newWidth, uint64_t newHeight);

    [[nodiscard]]
    Block& GetBlock(uint64_t x, uint64_t y);
    [[nodiscard]]
    bool_t GetCell(uint64_t blockX, uint64_t blockY, uint8_t cellX, uint8_t cellY);
    void SetCell(uint64_t blockX, uint64_t blockY, uint8_t cellX, uint8_t cellY, bool_t value);
    void ToggleCell(uint64_t blockX, uint64_t blockY, uint8_t cellX, uint8_t cellY);

private:
    Block* m_Blocks = nullptr;

    uint64_t m_Width = 0, m_Height = 0;

    Block m_Empty;
};
