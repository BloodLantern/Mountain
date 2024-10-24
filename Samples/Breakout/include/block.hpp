#pragma once

#include <Mountain/scene/entity.hpp>

constexpr float_t BlockSize = 50.f;

class Block : public Mountain::Entity
{
public:
    Block();
    ~Block() override;

    DEFAULT_COPY_MOVE_OPERATIONS(Block)
    
    void Update() override;
    void Render() override;
    void RenderDebug() override;
};
