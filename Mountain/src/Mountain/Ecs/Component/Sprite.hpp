#pragma once

#include <string>

#include "Mountain/Core.hpp"
#include "Mountain/Ecs/Component/Component.hpp"
#include "Mountain/Resource/Texture.hpp"
#include "Mountain/Containers/List.hpp"

// TODO - Make non-Component versions of Sprite and StateMachine

namespace Mountain
{
    class Sprite : public Component
    {
    public:
        std::string name;
        f32 frameDuration = 0.1f;

        Sprite() = default;
        MOUNTAIN_API explicit Sprite(std::string spriteName);
        MOUNTAIN_API Sprite(std::string spriteName, f32 frameDuration);

        /// @brief Initialize the Texture vector
        /// @warning This is a quite heavy operation as it loops over all loaded textures to find the right ones
        /// and is already called in the constructor.
        /// Consider using this only when necessary, i.e., after modifying @c name.
        MOUNTAIN_API void SetupTextures();

        MOUNTAIN_API const Pointer<Texture>& Get() const;

        GETTER(const List<Pointer<Texture>>&, Textures, m_Textures)
        GETTER(usize, CurrentIndex, m_CurrentIndex)
        GETTER(f32, UpdateTimer, m_UpdateTimer)

    protected:
        MOUNTAIN_API void Update() override;

    private:
        List<Pointer<Texture>> m_Textures;
        usize m_CurrentIndex = 0;

        f32 m_UpdateTimer = 0.f;
    };
}
