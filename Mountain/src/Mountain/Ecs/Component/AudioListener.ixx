export module Mountain:Ecs_Component_AudioListener;

import "Mountain/Core.hpp";

import :Core;
import :Ecs_Component_Component;

export namespace Mountain
{
    class MOUNTAIN_API AudioListener : public Component
    {
    public:
        bool_t dopplerEffect = false;

        void Update() override;

        /// @brief Get the volume in the range [0, inf].
        [[nodiscard]]
        float_t GetVolume() const;

        /// @brief Set the volume in the range [0, inf]. Default value is 1.
        void SetVolume(float_t newVolume);

    private:
        /// @brief Volume in the range [0, inf]. Default value is 1.
        float_t m_Volume = 1.f;

        Vector2 m_LastPosition;
    };
}
