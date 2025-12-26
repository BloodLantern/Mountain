#include "PrecompiledHeader.hpp"

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
    m_AudioSourceEntity = new Entity;
    m_AudioSource = m_AudioSourceEntity->AddComponent<AudioSource>();
    m_AudioSource->SetLooping(true);
    m_AudioSourceCollider = m_AudioSourceEntity->SetCollider<Circle>(Vector2::Zero(), 5.f);
    m_AudioSourceEntity->position = Window::GetSize() * 0.5f;

    m_Entities.AddNow(m_AudioSourceEntity);

    m_AudioListenerEntity = new Entity;
    m_AudioListener = m_AudioListenerEntity->AddComponent<AudioListener>();

    m_Entities.AddNow(m_AudioListenerEntity);
}

AudioScene::~AudioScene()
{
    delete m_AudioSourceEntity;
    delete m_AudioListenerEntity;
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

    m_AudioListenerEntity->position = Input::GetMousePosition();

    if (Input::GetMouseButton(MouseButton::Left, MouseButtonStatus::Pressed) && m_AudioSourceCollider->CheckCollision(Input::GetMousePosition()))
    {
        m_AudioSourceDragStart = Input::GetMousePosition();
        m_AudioSourceDragStartPosition = m_AudioSourceEntity->position;
    }

    if (m_AudioSourceDragStart.HasValue() && Input::GetMouseButton(MouseButton::Left, MouseButtonStatus::Down))
        m_AudioSourceEntity->position = m_AudioSourceDragStartPosition + Input::GetMousePosition() - m_AudioSourceDragStart.Value();

    if (Input::GetMouseButton(MouseButton::Left, MouseButtonStatus::Release))
        m_AudioSourceDragStart.Reset();
}

void AudioScene::Render()
{
    TestScene::Render();

    Draw::CircleFilled(m_AudioSourceEntity->position + m_AudioSourceCollider->offset, m_AudioSourceCollider->radius);
}

void AudioScene::RenderImGui()
{
    TestScene::RenderImGui();

    ImGui::TextWrapped("The white dot is where the spatialized audio source is located. Your mouse is an audio listener, try moving it near the dot!");

    if (ImGuiUtils::PushSeparatorText("Listener (mouse)"))
    {
        ImGui::DragFloat2("Position", m_AudioListenerEntity->position.Data());
        ImGui::Checkbox("Doppler effect", &m_AudioListener->dopplerEffect);
        IMGUI_GET_SET(ImGui::SliderFloat, "Volume", m_AudioListener->, Volume, 0.f, 1.f);

        ImGuiUtils::PopSeparatorText();
    }

    if (ImGuiUtils::PushSeparatorText("Spatialized source"))
    {
        if (ImGui::Button("Play"))
            m_AudioSource->Play();
        /*if (ImGui::Button("Stop")) // TODO - Stop m_AudioSource
            m_AudioSource->Stop();*/
        ImGui::DragFloat2("Position", m_AudioSourceEntity->position.Data());
        ImGui::SetItemTooltip("You can also drag and drop the dot");
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
