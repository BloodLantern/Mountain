#pragma once

#include "Common.hpp"

#include <Mountain/Ecs/Entity.hpp>
#include <Mountain/Ecs/Component/AudioListener.hpp>
#include <Mountain/Ecs/Component/AudioSource.hpp>

#include "Scenes/TestScene.hpp"

class AudioScene : public TestScene
{
public:
    using Base = TestScene;

    AudioScene();

    void LoadResources() override;

    void Begin() override;

    void Update() override;

    void Render() override;

    void RenderImGui() override;

    void End() override;

    void UnloadResources() override;

private:
    Entity* m_MouseEntity = nullptr;
    Entity* m_AudioListenerEntity = nullptr;
    Circle* m_AudioListenerCollider = nullptr;

    AudioListener* m_AudioListener = nullptr;
    AudioSource* m_AudioSource = nullptr;

    Pointer<AudioTrack> m_AudioSourceTrack;
    Pointer<AudioTrack> m_AudioPlayTrack;
    Pointer<AudioTrack> m_StereoAudioTrack;

    std::optional<Vector2> m_AudioListenerDragStart;
    Vector2 m_AudioListenerDragStartPosition;
};
