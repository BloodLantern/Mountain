#pragma once

#include <string>

#include "Mountain/core.hpp"
#include "Mountain/resource/texture.hpp"
#include "Mountain/scene/component/component.hpp"

BEGIN_MOUNTAIN

class Sprite : public Component
{
public:
    Sprite() = default;
    explicit Sprite(std::string spriteName);
    Sprite(std::string spriteName, float_t frameDuration);
    
    [[nodiscard]]
    const std::string& GetSpriteName() const;
    void SetSpriteName(const std::string& spriteName);
    
    [[nodiscard]]
    const std::vector<Pointer<Texture>>& GetSprites() const;
    
    [[nodiscard]]
    size_t GetCurrentSprite() const;
    
    [[nodiscard]]
    float_t GetFrameDuration() const;
    void SetFrameDuration(float_t frameDuration);
    
    [[nodiscard]]
    float_t GetUpdateTimer() const;

private:
    std::string m_SpriteName;

    std::vector<Pointer<Texture>> m_Sprites;
    size_t m_CurrentSprite = 0;

    float_t m_FrameDuration = 0.1f;
    float_t m_UpdateTimer = 0.f;

    void SetupSprites();
};

END_MOUNTAIN
