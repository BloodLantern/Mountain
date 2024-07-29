#pragma once

#include "resource/texture.hpp"
#include "scene/entity.hpp"
#include "utils/pointer.hpp"

// TODO - Add a state machine
// TODO - Add a way to handle sprite animations

class Player : public Mountain::Entity
{
public:
    float_t movementSpeed = 150.f;
    
    explicit Player(const Vector2& position);

    void LoadResources();
    void Update() override;
    void Render() override;
    
private:
	Mountain::Pointer<Mountain::Texture> m_Texture;
};
