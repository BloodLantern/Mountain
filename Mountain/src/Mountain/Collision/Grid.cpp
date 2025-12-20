#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Collision/Grid.hpp"

#include "Mountain/Collision/ColliderList.hpp"
#include "Mountain/Collision/Hitbox.hpp"
#include "Mountain/Graphics/Draw.hpp"

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
    for (s32 y = 0; y < gridSize.y; y++)
    {
        for (s32 x = 0; x < gridSize.x; x++)
        {
            if (!tiles[y][x])
                continue;

            if (y > 0 && !tiles[y - 1][x])
            {
                Draw::Line(
                    position + Vector2(
                        static_cast<f32>(x) * tileSize.x,
                        static_cast<f32>(y) * tileSize.y
                    ),
                    position + Vector2(
                        static_cast<f32>(x + 1) * tileSize.x,
                        static_cast<f32>(y) * tileSize.y
                    ),
                    1.f,
                    color
                );
            }
            if (x > 0 && !tiles[y][x - 1])
            {
                Draw::Line(
                    position + Vector2(
                        static_cast<f32>(x) * tileSize.x,
                        static_cast<f32>(y) * tileSize.y
                    ),
                    position + Vector2(
                        static_cast<f32>(x) * tileSize.x,
                        static_cast<f32>(y + 1) * tileSize.y
                    ),
                    1.f,
                    color
                );
            }
            if (y < gridSize.y - 1 && !tiles[y + 1][x])
            {
                Draw::Line(
                    position + Vector2(
                        static_cast<f32>(x) * tileSize.x,
                        static_cast<f32>(y + 1) * tileSize.y
                    ),
                    position + Vector2(
                        static_cast<f32>(x + 1) * tileSize.x,
                        static_cast<f32>(y + 1) * tileSize.y
                    ),
                    1.f,
                    color
                );
            }
            if (x < gridSize.x - 1 && !tiles[y][x + 1])
            {
                Draw::Line(
                    position + Vector2(
                        static_cast<f32>(x + 1) * tileSize.x,
                        static_cast<f32>(y) * tileSize.y
                    ),
                    position + Vector2(
                        static_cast<f32>(x + 1) * tileSize.x,
                        static_cast<f32>(y + 1) * tileSize.y
                    ),
                    1.f,
                    color
                );
            }
        }
    }
}

bool Grid::CheckCollision(const Vector2 point) const
{
    return point.x >= AbsoluteLeft()
        && point.y >= AbsoluteTop()
        && point.x < AbsoluteRight()
        && point.y < AbsoluteBottom()
        && tiles[static_cast<u32>((point.y - AbsoluteTop()) / tileSize.y)][static_cast<u32>((point.x - AbsoluteLeft()) / tileSize.x)];
}

bool Grid::CheckCollision(const Hitbox& hitbox) const
{
    if (!Hitbox(GetActualPosition(), gridSize * tileSize).Intersects(hitbox))
        return false;

    s32 x = static_cast<s32>((hitbox.AbsoluteLeft() - AbsoluteLeft()) / tileSize.x);
    s32 y = static_cast<s32>((hitbox.AbsoluteTop() - AbsoluteTop()) / tileSize.y);

    const f32 subTileRight = (hitbox.AbsoluteRight() - AbsoluteLeft()) / tileSize.x;
    s32 tileRight = static_cast<s32>(subTileRight);
    if (static_cast<f32>(tileRight) != subTileRight)
        tileRight += 1;
    s32 width =  tileRight - x;
    const f32 subTileBottom = (hitbox.AbsoluteBottom() - AbsoluteTop()) / tileSize.y;
    s32 tileBottom = static_cast<s32>(subTileBottom);
    if (static_cast<f32>(tileBottom) != subTileBottom)
        tileBottom += 1;
    s32 height =  tileBottom - y;

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

    for (s32 i = 0; i < width; i++)
    {
        for (s32 j = 0; j < height; j++)
        {
            if (tiles[y + j][x + i])
                return true;
        }
    }

    return false;
}

bool Grid::CheckCollision(const Circle&) const
{
    THROW(NotImplementedException{"Currently cannot check collision between grid and circle (should be implemented at some point)"});
}

bool Grid::CheckCollision(const Grid&) const
{
    THROW(InvalidOperationException{"Cannot check collision between grids"});
}

bool Grid::CheckCollision(const ColliderList& list) const { return list.CheckCollision(*this); }

f32 Grid::Left() const { return offset.x; }

f32 Grid::Right() const { return offset.x + Width(); }

f32 Grid::Top() const { return offset.y; }

f32 Grid::Bottom() const { return offset.y + Height(); }

f32 Grid::AbsoluteLeft() const { return GetActualPosition().x; }

f32 Grid::AbsoluteRight() const { return GetActualPosition().x + Width(); }

f32 Grid::AbsoluteTop() const { return GetActualPosition().y; }

f32 Grid::AbsoluteBottom() const { return GetActualPosition().y + Height(); }

f32 Grid::Width() const { return static_cast<f32>(gridSize.x) * tileSize.x; }

f32 Grid::Height() const { return static_cast<f32>(gridSize.y) * tileSize.y; }

Vector2 Grid::Size() const { return gridSize * tileSize; }

List<bool>& Grid::operator[](const usize y) { return tiles[y]; }

const List<bool>& Grid::operator[](const usize y) const { return tiles[y]; }

bool Grid::At(const usize y, const usize x) const { return tiles[y][x]; }

bool Grid::At(const Vector2i tilePosition) const { return tiles[tilePosition.y][tilePosition.x]; }

void Grid::ResizeGrid()
{
    tiles.Resize(gridSize.y);

    for (auto&& row : tiles)
        row.Resize(gridSize.x);
}
