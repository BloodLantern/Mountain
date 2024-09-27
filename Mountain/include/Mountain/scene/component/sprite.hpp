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

    void Update() override;

    /// @brief Initialize the Texture vector
    /// @warning This is a heavy operation and is already called in the constructor.
    /// Consider using this only when necessary, e.g. after using either SetName() or SetFrameDuration()
    void SetupTextures();

    const Pointer<Texture>& Get();
    
    [[nodiscard]]
    const std::string& GetName() const;
    void SetName(const std::string& name);
    
    [[nodiscard]]
    const std::vector<Pointer<Texture>>& GetTextures() const;
    
    [[nodiscard]]
    size_t GetCurrentIndex() const;
    
    [[nodiscard]]
    float_t GetFrameDuration() const;
    void SetFrameDuration(float_t frameDuration);
    
    [[nodiscard]]
    float_t GetUpdateTimer() const;

private:
    std::string m_Name;

    std::vector<Pointer<Texture>> m_Textures;
    size_t m_CurrentIndex = 0;

    float_t m_FrameDuration = 0.1f;
    float_t m_UpdateTimer = 0.f;
};

END_MOUNTAIN
