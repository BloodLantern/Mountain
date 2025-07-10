#pragma once

#include <string>

#include "Mountain/Core.hpp"
#include "Mountain/Ecs/Component/Component.hpp"
#include "Mountain/Resource/Texture.hpp"
#include "Mountain/Containers/List.hpp"

namespace Mountain
{
    class Sprite : public Component
    {
    public:
        std::string name;
        float_t frameDuration = 0.1f;

        MOUNTAIN_API Sprite() = default;
        MOUNTAIN_API explicit Sprite(std::string spriteName);
        MOUNTAIN_API Sprite(std::string spriteName, float_t frameDuration);

        /// @brief Initialize the Texture vector
        /// @warning This is a quite heavy operation as it loops over all loaded textures to find the right ones
        /// and is already called in the constructor.
        /// Consider using this only when necessary, i.e., after modifying @c name.
        MOUNTAIN_API void SetupTextures();

        MOUNTAIN_API const Pointer<Texture>& Get() const;

        GETTER(const List<Pointer<Texture>>&, Textures, m_Textures)
        GETTER(size_t, CurrentIndex, m_CurrentIndex)
        GETTER(float_t, UpdateTimer, m_UpdateTimer)

    protected:
        void Update() override;

    private:
        List<Pointer<Texture>> m_Textures;
        size_t m_CurrentIndex = 0;

        float_t m_UpdateTimer = 0.f;
    };
}
