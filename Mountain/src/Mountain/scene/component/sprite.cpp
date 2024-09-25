#include "Mountain/scene/component/sprite.hpp"

#include "Mountain/resource/resource_manager.hpp"

using namespace Mountain;

Sprite::Sprite(std::string spriteName)
    : m_SpriteName(std::move(spriteName))
{
    SetupSprites();
}

Sprite::Sprite(std::string spriteName, const float_t frameDuration)
    : m_SpriteName(std::move(spriteName))
    , m_FrameDuration(frameDuration)
{
    SetupSprites();
}

const std::string& Sprite::GetSpriteName() const { return m_SpriteName; }

void Sprite::SetSpriteName(const std::string& spriteName)
{
    m_SpriteName = spriteName;
    SetupSprites();
}

float_t Sprite::GetFrameDuration() const { return m_FrameDuration; }

void Sprite::SetFrameDuration(const float_t frameDuration) { m_FrameDuration = frameDuration; }

const std::vector<Pointer<Texture>>& Sprite::GetSprites() const { return m_Sprites; }

size_t Sprite::GetCurrentSprite() const { return m_CurrentSprite; }

float_t Sprite::GetUpdateTimer() const { return m_UpdateTimer; }

void Sprite::SetupSprites()
{
    m_Sprites.clear();
    ResourceManager::FindAll<Texture>(
        [this](const Pointer<Texture>& t) -> bool_t
        {
            const std::string& name = t->GetName();
            if (!name.starts_with(m_SpriteName))
                return false;

            if (std::filesystem::path{name}.stem())

            return true;
        },
        &m_Sprites
    );
}
