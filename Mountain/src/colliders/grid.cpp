#include "grid.hpp"

#include "hitbox.hpp"
#include "draw.hpp"

bool* const* const SetupGrid(const Vector2i size)
{
    bool** grid = new bool*[size.x];
    for (int i = 0; i < size.x; i++)
    {
        grid[i] = new bool[size.y];
        for (int j = 0; j < size.y; j++)
            grid[i][j] = false;
    }
    return grid;
}

mountain::Grid::Grid(const Vector2i size, const Vector2 tileSize)
    : GridSize(size),
    TileSize(tileSize),
    Tiles(SetupGrid(size))
{
}

mountain::Grid::Grid(const Vector2i size, const Vector2 tileSize, const Vector2 position)
    : Collider(position),
    GridSize(size),
    TileSize(tileSize),
    Tiles(SetupGrid(size))
{
}

mountain::Grid::~Grid()
{
    for (int i = 0; i < GridSize.x; i++)
        delete[] Tiles[i];
    delete[] Tiles;
}

void mountain::Grid::Draw(const Color color) const
{
    for (int i = 0; i < GridSize.x; i++)
        for (int j = 0; j < GridSize.y; j++)
            if (Tiles[i][j])
            {
                if (i > 0)
                    if (!Tiles[i - 1][j])
                        Draw::Line(Position + Vector2(i * TileSize.x, j * TileSize.y), Position + Vector2(i * TileSize.x, (j + 1) * TileSize.y), color);
                if (j > 0)
                    if (!Tiles[i][j - 1])
                        Draw::Line(Position + Vector2(i * TileSize.x, j * TileSize.y), Position + Vector2((i + 1) * TileSize.x, j * TileSize.y), color);
                if (i < GridSize.x - 1)
                    if (!Tiles[i + 1][j])
                        Draw::Line(Position + Vector2((i + 1) * TileSize.x, j * TileSize.y), Position + Vector2((i + 1) * TileSize.x, (j + 1) * TileSize.y), color);
                if (j < GridSize.y - 1)
                    if (!Tiles[i][j + 1])
                        Draw::Line(Position + Vector2(i * TileSize.x, (j + 1) * TileSize.y), Position + Vector2((i + 1) * TileSize.x, (j + 1) * TileSize.y), color);
            }
}

bool mountain::Grid::CheckCollision(const Vector2& point) const
{
    return point.x >= Left()
        && point.y >= Top()
        && point.x < Right()
        && point.y < Bottom()
        && Tiles[(unsigned int) ((point.x - Left()) / TileSize.x)][(unsigned int) ((point.y - Top()) / TileSize.y)];
}

bool mountain::Grid::CheckCollision(const Hitbox& hitbox) const
{
    if (!hitbox.Intersects(Hitbox(Position, GridSize)))
        return false;

    int x = (int) ((hitbox.Left() - Left()) / TileSize.x);
    int y = (int) ((hitbox.Top() - Top()) / TileSize.y);
    int width = (int) ((hitbox.Right() - Left() - 1) / TileSize.x) - x + 1;
    int height = (int) ((hitbox.Bottom() - Top() - 1) / TileSize.y) - y + 1;

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

    if (x + width > GridSize.x)
        width = GridSize.x - x;
    if (y + height > GridSize.y)
        height = GridSize.y - y;

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            if (Tiles[x + i][y + j])
                return true;

    return false;
}

bool mountain::Grid::CheckCollision(const Circle&) const
{
    throw std::runtime_error("Cannot check collision between grid and circle.");
}

bool mountain::Grid::CheckCollision(const Grid&) const
{
    throw std::runtime_error("Cannot check collision between grids.");
}
