#include "collision/grid.hpp"

#include "draw.hpp"
#include "collision/collider_list.hpp"
#include "collision/hitbox.hpp"

using namespace Mountain;

Grid::Grid(const Vector2i size, const Vector2 tileSize)
    : Collider(ColliderType::Grid)
    , gridSize(size)
    , tileSize(tileSize)
{
    ResizeGrid();
}

Grid::Grid(const Vector2i size, const Vector2 tileSize, const Vector2 position)  // NOLINT(clang-diagnostic-shadow-field)
    : Collider(ColliderType::Grid, position)
    , gridSize(size)
    , tileSize(tileSize)
{
    ResizeGrid();
}

void Grid::DebugRender(const Color& color) const
{
    for (int32_t i = 0; i < gridSize.x; i++)
    {
        for (int32_t j = 0; j < gridSize.y; j++)
        {
            if (tiles[i][j])
            {
                if (i > 0)
                {
                    if (!tiles[i - 1][j])
                        Draw::Line(position + Vector2(static_cast<float_t>(i) * tileSize.x, static_cast<float_t>(j) * tileSize.y), position + Vector2(static_cast<float_t>(i) * tileSize.x, static_cast<float_t>(j + 1) * tileSize.y), color);
                }
                if (j > 0)
                {
                    if (!tiles[i][j - 1])
                        Draw::Line(position + Vector2(static_cast<float_t>(i) * tileSize.x, static_cast<float_t>(j) * tileSize.y), position + Vector2(static_cast<float_t>(i + 1) * tileSize.x, static_cast<float_t>(j) * tileSize.y), color);
                }
                if (i < gridSize.x - 1)
                {
                    if (!tiles[i + 1][j])
                        Draw::Line(position + Vector2(static_cast<float_t>(i + 1) * tileSize.x, static_cast<float_t>(j) * tileSize.y), position + Vector2(static_cast<float_t>(i + 1) * tileSize.x, static_cast<float_t>(j + 1) * tileSize.y), color);
                }
                if (j < gridSize.y - 1)
                {
                    if (!tiles[i][j + 1])
                        Draw::Line(position + Vector2(static_cast<float_t>(i) * tileSize.x, static_cast<float_t>(j + 1) * tileSize.y), position + Vector2(static_cast<float_t>(i + 1) * tileSize.x, static_cast<float_t>(j + 1) * tileSize.y), color);
                }
            }
        }
    }
}

bool_t Grid::CheckCollision(const Vector2& point) const
{
    return point.x >= Left()
        && point.y >= Top()
        && point.x < Right()
        && point.y < Bottom()
        && tiles[static_cast<uint32_t>((point.x - Left()) / tileSize.x)][static_cast<uint32_t>((point.y - Top()) / tileSize.y)];
}

bool_t Grid::CheckCollision(const Hitbox& hitbox) const
{
    if (!hitbox.Intersects(Hitbox(position, static_cast<Vector2>(gridSize))))
        return false;

    int32_t x = static_cast<int32_t>((hitbox.Left() - Left()) / tileSize.x);
    int32_t y = static_cast<int32_t>((hitbox.Top() - Top()) / tileSize.y);
    int32_t width = static_cast<int32_t>((hitbox.Right() - Left() - 1) / tileSize.x) - x + 1;
    int32_t height = static_cast<int32_t>((hitbox.Bottom() - Top() - 1) / tileSize.y) - y + 1;

    if (x < 0)
    {
        width += x;
        x = 0;
    }
    if (y < 0)
    {
        height += y;
        y = 0;
    }

    if (x + width > gridSize.x)
        width = gridSize.x - x;
    if (y + height > gridSize.y)
        height = gridSize.y - y;

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (tiles[x + i][y + j])
                return true;
        }
    }

    return false;
}

bool_t Grid::CheckCollision(const Circle&) const
{
    throw std::runtime_error("Cannot check collision between grid and circle.");
}

bool_t Grid::CheckCollision(const Grid&) const
{
    throw std::runtime_error("Cannot check collision between grids.");
}

bool_t Grid::CheckCollision(const ColliderList& list) const { return list.CheckCollision(*this); }

float_t Grid::Left() const { return position.x; }

float_t Grid::Right() const { return position.x + Width(); }

float_t Grid::Top() const { return position.y; }

float_t Grid::Bottom() const { return position.y + Height(); }

Vector2 Grid::Center() const { return position + Size() * 0.5f; }

float_t Grid::Width() const { return static_cast<float_t>(gridSize.x) * tileSize.x; }

float_t Grid::Height() const { return static_cast<float_t>(gridSize.y) * tileSize.y; }

Vector2 Grid::Size() const { return static_cast<Vector2>(gridSize) * tileSize; }

void Grid::ResizeGrid()
{
    tiles.Resize(gridSize.x);

    for (auto&& col : tiles)
        col.Resize(gridSize.y);
}
