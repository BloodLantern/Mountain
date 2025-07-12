#pragma once

namespace Mountain::Audio
{
    class MOUNTAIN_API Listener
    {
    public:
        explicit Listener();

        void SetPosition(Vector2 position, bool_t updateVelocity = false);
        void SetVelocity(Vector2 velocity);
        void SetVolume(float_t volume);

        ATTRIBUTE_NODISCARD
        float_t GetVolume() const;

    private:
        float_t m_Volume;
        Vector2 m_Position;
        Vector2 m_Velocity;
    };
}
