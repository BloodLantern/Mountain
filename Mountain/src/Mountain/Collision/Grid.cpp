#include "Mountain/Collision/Grid.hpp"

#include "Mountain/Collision/ColliderList.hpp"
#include "Mountain/Collision/Hitbox.hpp"
#include "Mountain/Rendering/Draw.hpp"

using namespace Mountain;

Grid::Grid()
    : Collider(ColliderType::Grid)
{
}

Grid::Grid(const Vector2i size, const Vector2 tileSize)
    : Collider(ColliderType::Grid)
    , gridSize(size)
    , tileSize(tileSize)
{
    ResizeGrid();
}

Grid::Grid(const Vector2i size, const Vector2 tileSize, const Vector2 off)
    : Collider(ColliderType::Grid, off)
    , gridSize(size)
    , tileSize(tileSize)
{
    ResizeGrid();
}

void Grid::RenderDebug(const Color& color) const
{
    const Vector2 position = GetActualPosition();
    for (int32_t y = 0; y < gridSize.y; y++)
    {
        for (int32_t x = 0; x < gridSize.x; x++)
        {
            if (!tiles[y][x])
                continue;

            if (y > 0 && !tiles[y - 1][x])
            {
                Draw::Line(
                    position + Vector2(
                        static_cast<float_t>(x) * tileSize.x,
                        static_cast<float_t>(y) * tileSize.y
                    ),
                    position + Vector2(
                        static_cast<float_t>(x + 1) * tileSize.x,
                        static_cast<float_t>(y) * tileSize.y
                    ),
                    color
                );
            }
            if (x > 0 && !tiles[y][x - 1])
            {
                Draw::Line(
                    position + Vector2(
                        static_cast<float_t>(x) * tileSize.x,
                        static_cast<float_t>(y) * tileSize.y
                    ),
                    position + Vector2(
                        static_cast<float_t>(x) * tileSize.x,
                        static_cast<float_t>(y + 1) * tileSize.y
                    ),
                    color
                );
            }
            if (y < gridSize.y - 1 && !tiles[y + 1][x])
            {
                Draw::Line(
                    position + Vector2(
                        static_cast<float_t>(x) * tileSize.x,
                        static_cast<float_t>(y + 1) * tileSize.y
                    ),
                    position + Vector2(
                        static_cast<float_t>(x + 1) * tileSize.x,
                        static_cast<float_t>(y + 1) * tileSize.y
                    ),
                    color
                );
            }
            if (x < gridSize.x - 1 && !tiles[y][x + 1])
            {
                Draw::Line(
                    position + Vector2(
                        static_cast<float_t>(x + 1) * tileSize.x,
                        static_cast<float_t>(y) * tileSize.y
                    ),
                    position + Vector2(
                        static_cast<float_t>(x + 1) * tileSize.x,
                        static_cast<float_t>(y + 1) * tileSize.y
                    ),
                    color
                );
            }
        }
    }
}

bool_t Grid::CheckCollision(const Vector2 point) const
{
    return point.x >= AbsoluteLeft()
        && point.y >= AbsoluteTop()
        && point.x < AbsoluteRight()
        && point.y < AbsoluteBottom()
        && tiles[static_cast<uint32_t>((point.y - AbsoluteTop()) / tileSize.y)][static_cast<uint32_t>((point.x - AbsoluteLeft()) / tileSize.x)];
}

bool_t Grid::CheckCollision(const Hitbox& hitbox) const
{
    if (!Hitbox(GetActualPosition(), gridSize * tileSize).Intersects(hitbox))
        return false;

    int32_t x = static_cast<int32_t>((hitbox.AbsoluteLeft() - AbsoluteLeft()) / tileSize.x);
    int32_t y = static_cast<int32_t>((hitbox.AbsoluteTop() - AbsoluteTop()) / tileSize.y);

    const float_t subTileRight = (hitbox.AbsoluteRight() - AbsoluteLeft()) / tileSize.x;
    int32_t tileRight = static_cast<int32_t>(subTileRight);
    if (static_cast<float_t>(tileRight) != subTileRight)
        tileRight += 1;
    int32_t width =  tileRight - x;
    const float_t subTileBottom = (hitbox.AbsoluteBottom() - AbsoluteTop()) / tileSize.y;
    int32_t tileBottom = static_cast<int32_t>(subTileBottom);
    if (static_cast<float_t>(tileBottom) != subTileBottom)
        tileBottom += 1;
    int32_t height =  tileBottom - y;

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

    for (int32_t i = 0; i < width; i++)
    {
        for (int32_t j = 0; j < height; j++)
        {
            if (tiles[y + j][x + i])
                return true;
        }
    }

    return false;
}

bool_t Grid::CheckCollision(const Circle&) const
{
    THROW(NotImplementedException{"Currently cannot check collision between grid and circle (should be implemented at some point)"});
}

bool_t Grid::CheckCollision(const Grid&) const
{
    THROW(InvalidOperationException{"Cannot check collision between grids"});
}

bool_t Grid::CheckCollision(const ColliderList& list) const { return list.CheckCollision(*this); }

float_t Grid::Left() const { return offset.x; }

float_t Grid::Right() const { return offset.x + Width(); }

float_t Grid::Top() const { return offset.y; }

float_t Grid::Bottom() const { return offset.y + Height(); }

float_t Grid::AbsoluteLeft() const { return GetActualPosition().x; }

float_t Grid::AbsoluteRight() const { return GetActualPosition().x + Width(); }

float_t Grid::AbsoluteTop() const { return GetActualPosition().y; }

float_t Grid::AbsoluteBottom() const { return GetActualPosition().y + Height(); }

float_t Grid::Width() const { return static_cast<float_t>(gridSize.x) * tileSize.x; }

float_t Grid::Height() const { return static_cast<float_t>(gridSize.y) * tileSize.y; }

Vector2 Grid::Size() const { return gridSize * tileSize; }

List<bool_t>& Grid::operator[](const size_t y) { return tiles[y]; }

const List<bool_t>& Grid::operator[](const size_t y) const { return tiles[y]; }

bool_t Grid::At(const size_t y, const size_t x) const { return tiles[y][x]; }

bool_t Grid::At(const Vector2i tilePosition) const { return tiles[tilePosition.y][tilePosition.x]; }

void Grid::ResizeGrid()
{
    tiles.Resize(gridSize.y);

    for (auto&& row : tiles)
        row.Resize(gridSize.x);
}
