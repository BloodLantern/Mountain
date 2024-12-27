#pragma once

#include "block.hpp"
#include "Mountain/rendering/render_target.hpp"

template <>
struct std::hash<std::pair<uint64_t, uint64_t>>
{
    static constexpr size_t RandomValue = 0x923A59B9;

    size_t operator()(const std::pair<uint64_t, uint64_t>& value) const noexcept
    {
        size_t result = 0;
        result ^= std::hash<decltype(value.first)>()(value.first) + RandomValue;
        result ^= std::hash<decltype(value.second)>()(value.second) + RandomValue + (result << 6) + (result >> 2);

        return result;
    }
};

constexpr float_t GridPreRenderGridFactor = 10.f;

class Grid
{
public:
    Grid() = default;
    ~Grid();

    DELETE_COPY_MOVE_OPERATIONS(Grid)

    void Update();
    void PreRenderGrid();
    void Render();

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

    Mountain::RenderTarget m_RenderTarget;
};
