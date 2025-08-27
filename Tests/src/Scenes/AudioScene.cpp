#include "Common.hpp"

#include "Scenes/AudioScene.hpp"

#include <Mountain/Collision/Circle.hpp>
#include <Mountain/FileSystem/FileManager.hpp>
#include <Mountain/Input/Input.hpp>
#include <Mountain/Graphics/Draw.hpp>
#include <Mountain/Resource/ResourceManager.hpp>
#include <Mountain/Utils/ImGuiUtils.hpp>

AudioScene::AudioScene()
    : Base{"Audio"}
{
    m_MouseEntity = new Entity;
    m_AudioSource = m_MouseEntity->AddComponent<AudioSource>();
    m_AudioSource->SetLooping(true);

    m_Entities.AddNow(m_MouseEntity);

    m_AudioListenerEntity = new Entity;
    m_AudioListener = m_AudioListenerEntity->AddComponent<AudioListener>();
    m_AudioListenerCollider = m_AudioListenerEntity->SetCollider<Circle>(Vector2::Zero(), 5.f);

    m_Entities.AddNow(m_AudioListenerEntity);

    m_AudioListenerEntity->position = Window::GetSize() * 0.5f;
}

void AudioScene::LoadPersistentResources()
{
    TestScene::LoadPersistentResources();

    m_AudioPlayTrack = ResourceManager::Get<AudioTrack>("assets/metal-pipe.wav");
    m_StereoAudioTrack = ResourceManager::Get<AudioTrack>("assets/music.mp3");
    m_AudioSourceTrack = ResourceManager::Get<AudioTrack>("assets/sfx.ogg");

    m_AudioSource->audioTrack = m_AudioSourceTrack;
}

void AudioScene::Begin()
{
    TestScene::Begin();
}

void AudioScene::Update()
{
    TestScene::Update();

    m_MouseEntity->position = Input::GetMousePosition();

    if (Input::GetMouseButton(MouseButton::Left, MouseButtonStatus::Pressed) && m_AudioListenerCollider->CheckCollision(Input::GetMousePosition()))
    {
        m_AudioListenerDragStart = Input::GetMousePosition();
        m_AudioListenerDragStartPosition = m_AudioListenerEntity->position;
    }

    if (m_AudioListenerDragStart.has_value() && Input::GetMouseButton(MouseButton::Left, MouseButtonStatus::Down))
        m_AudioListenerEntity->position = m_AudioListenerDragStartPosition + Input::GetMousePosition() - m_AudioListenerDragStart.value();

    if (Input::GetMouseButton(MouseButton::Left, MouseButtonStatus::Release))
        m_AudioListenerDragStart.reset();
}

void AudioScene::Render()
{
    TestScene::Render();

    Draw::CircleFilled(m_AudioListenerEntity->position + m_AudioListenerCollider->offset, m_AudioListenerCollider->radius);
}

void AudioScene::RenderImGui()
{
    TestScene::RenderImGui();

    ImGui::TextWrapped("The white dot is where the audio listener is located. Your mouse is a spatialized audio source, try moving it near the dot!");

    if (ImGuiUtils::PushSeparatorText("Listener"))
    {
        ImGui::DragFloat2("Position", m_AudioListenerEntity->position.Data());
        ImGui::SetItemTooltip("You can also drag and drop the dot");
        ImGui::Checkbox("Doppler effect", &m_AudioListener->dopplerEffect);
        IMGUI_GET_SET(ImGui::SliderFloat, "Volume", m_AudioListener->, Volume, 0.f, 1.f);

        ImGuiUtils::PopSeparatorText();
    }

    if (ImGuiUtils::PushSeparatorText("Spatialized source (mouse)"))
    {
        if (ImGui::Button("Play"))
            m_AudioSource->Play();
        /*if (ImGui::Button("Stop")) // TODO - Stop m_AudioSource
            m_AudioSource->Stop();*/
        IMGUI_GET_SET(ImGui::SliderFloat, "Volume", m_AudioSource->, Volume, 0.f, 1.f);
        IMGUI_GET_SET(ImGui::SliderFloat, "Pitch", m_AudioSource->, Pitch, 0.f, 2.f);
        IMGUI_GET_SET(ImGui::Checkbox, "Looping", m_AudioSource->, Looping);

        ImGuiUtils::PopSeparatorText();
    }

    if (ImGuiUtils::PushSeparatorText("Global stereo source"))
    {
        /*if (ImGui::Button("Play")) // TODO - Sound::Play
            Sound::Play(m_StereoAudioTrack);*/

        ImGuiUtils::PopSeparatorText();
    }
}

void AudioScene::End()
{
    // TODO - Stop m_AudioSource

    TestScene::End();
}
