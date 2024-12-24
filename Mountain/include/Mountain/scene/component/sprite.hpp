#pragma once

#include <string>

#include "Mountain/core.hpp"
#include "Mountain/resource/texture.hpp"
#include "Mountain/scene/component/component.hpp"
#include "Mountain/utils/list.hpp"

namespace Mountain
{
    class Sprite : public Component
    {
    public:
        MOUNTAIN_API Sprite() = default;
        MOUNTAIN_API explicit Sprite(std::string spriteName);
        MOUNTAIN_API Sprite(std::string spriteName, float_t frameDuration);

        /// @brief Initialize the Texture vector
        /// @warning This is a quite heavy operation as it loops over all loaded textures to find the right ones
        /// and is already called in the constructor. Consider using this only when necessary, e.g. after using SetName()
        MOUNTAIN_API void SetupTextures();

        MOUNTAIN_API const Pointer<Texture>& Get();

        [[nodiscard]]
        MOUNTAIN_API const std::string& GetName() const;
        MOUNTAIN_API void SetName(const std::string& name);

        [[nodiscard]]
        MOUNTAIN_API const List<Pointer<Texture>>& GetTextures() const;

        [[nodiscard]]
        MOUNTAIN_API size_t GetCurrentIndex() const;

        [[nodiscard]]
        MOUNTAIN_API float_t GetFrameDuration() const;
        MOUNTAIN_API void SetFrameDuration(float_t frameDuration);

        [[nodiscard]]
        MOUNTAIN_API float_t GetUpdateTimer() const;

    protected:
        void Update() override;

    private:
        std::string m_Name;

        List<Pointer<Texture>> m_Textures;
        size_t m_CurrentIndex = 0;

        float_t m_FrameDuration = 0.1f;
        float_t m_UpdateTimer = 0.f;
    };
}
