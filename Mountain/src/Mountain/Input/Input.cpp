

#include "Mountain/Input/Input.hpp"

#include "Time.hpp"
#include "Mountain/Utils/Logger.hpp"
#include "SDL3/SDL_gamepad.h"

using namespace Mountain;

bool Input::GetKey(const Key key, const KeyStatus status)
{
    return m_Keyboard.At(static_cast<usize>(key)).At(static_cast<usize>(status));
}

bool Input::GetMouseButton(const MouseButton mouseButton, const MouseButtonStatus status)
{
    return m_Mouse.At(static_cast<usize>(mouseButton)).At(static_cast<usize>(status));
}

const GamepadInput& Input::GetGamepad(const u32 gamepadId)
{
    if (gamepadId > GamepadMax)
        THROW(ArgumentException{"Invalid gamepad ID", "gamepadId"});

    return m_Gamepads.At(gamepadId);
}

u32 Input::GetGamepadsConnected()
{
    return static_cast<u32>(std::ranges::count_if(m_Gamepads, [](auto&& gamepad) -> bool { return gamepad.m_IsConnected; }));
}

bool Input::IsGamepadConnected(const u32 index) { return m_Gamepads[index].m_IsConnected; }

Vector2 Input::GetMousePosition() { return m_MousePosition; }

void Input::HandleKeyboard(const usize key, const KeyAction action)
{
    if (key > m_Keyboard.GetSize())
        return;

    KeyStatuses& keyStatuses = m_Keyboard.At(key);

    switch (action)
    {
        case KeyAction::Release:
            keyStatuses.At(static_cast<usize>(KeyStatus::Down)) = false;
            keyStatuses.At(static_cast<usize>(KeyStatus::Release)) = true;
            keyStatuses.At(static_cast<usize>(KeyStatus::Repeat)) = false;
            break;

        case KeyAction::Press:
            keyStatuses.At(static_cast<usize>(KeyStatus::Pressed)) = true;
            keyStatuses.At(static_cast<usize>(KeyStatus::Down)) = true;
            break;

        case KeyAction::Repeat:
            keyStatuses.At(static_cast<usize>(KeyStatus::Repeat)) = true;
            break;
    }
}

void Input::HandleMouseButton(const usize mouseButton, const bool pressed)
{
    MouseStatuses& keyStatuses = m_Mouse.At(mouseButton);

    if (pressed)
    {
        keyStatuses.At(static_cast<usize>(MouseButtonStatus::Pressed)) = true;
        keyStatuses.At(static_cast<usize>(MouseButtonStatus::Down)) = true;
    }
    else
    {
        keyStatuses.At(static_cast<usize>(MouseButtonStatus::Down)) = false;
        keyStatuses.At(static_cast<usize>(MouseButtonStatus::Release)) = true;
    }
}

void Input::HandleMouseMovement(const Vector2 newPosition)
{
    m_LastMousePosition = m_MousePosition;

    m_MousePosition = newPosition;
    m_MouseDelta = m_MousePosition - m_LastMousePosition;
}

void Input::HandleMouseWheel(const s32 wheelX, const s32 wheelY)
{
    m_MouseWheel += { static_cast<f32>(wheelX), static_cast<f32>(wheelY) };
}

void Input::ConnectGamepad(const u32 id)
{
    if (id == 0)
        return;

    GamepadInput* gamepad = m_Gamepads.FindFirst([](const GamepadInput& g) { return !g.m_IsConnected; });

    if (!gamepad)
        return;

    gamepad->m_Id = id;
    gamepad->m_Handle = SDL_OpenGamepad(id);
    gamepad->m_Name = SDL_GetGamepadName(gamepad->m_Handle);
    gamepad->m_IsConnected = true;

    // Assume there is no battery first, if there's one we should receive an event about it
    gamepad->m_Battery = -1;
    gamepad->m_BatteryState = GamepadBatteryState::NoBattery;

    GamepadCapabilities capabilities = GamepadCapabilities::None;

    const SDL_PropertiesID properties = SDL_GetGamepadProperties(gamepad->m_Handle);

    if (SDL_HasProperty(properties, SDL_PROP_GAMEPAD_CAP_RGB_LED_BOOLEAN))
    {
        capabilities |= GamepadCapabilities::Led;
    }

    if (SDL_HasProperty(properties, SDL_PROP_GAMEPAD_CAP_RUMBLE_BOOLEAN) ||
        SDL_HasProperty(properties, SDL_PROP_GAMEPAD_CAP_TRIGGER_RUMBLE_BOOLEAN))
    {
        capabilities |= GamepadCapabilities::Rumble;
    }

    const s32 nbrTouchpads = SDL_GetNumGamepadTouchpads(gamepad->m_Handle);
    if (nbrTouchpads != 0)
    {
        capabilities |= GamepadCapabilities::Touchpad;
        gamepad->m_Touchpads.Resize(nbrTouchpads);

        for (s32 i = 0; i < nbrTouchpads; i++)
        {
            gamepad->m_Touchpads[i].nbrOfFingersMax = static_cast<u8>(SDL_GetNumGamepadTouchpadFingers(gamepad->m_Handle, i));
            gamepad->m_Touchpads[i].fingerLocations.Fill({ -1, -1 });
        }
    }

    if (SDL_GamepadHasSensor(gamepad->m_Handle, SDL_SENSOR_ACCEL))
    {
        capabilities |= GamepadCapabilities::Accelerometer;
        SDL_SetGamepadSensorEnabled(gamepad->m_Handle, SDL_SENSOR_ACCEL, true);
    }

    if (SDL_GamepadHasSensor(gamepad->m_Handle, SDL_SENSOR_GYRO))
    {
        capabilities |= GamepadCapabilities::Gyroscope;
        SDL_SetGamepadSensorEnabled(gamepad->m_Handle, SDL_SENSOR_GYRO, true);
    }

    gamepad->m_Capabilities = capabilities;

    if (gamepad->HasCapability(GamepadCapabilities::Led))
        gamepad->SetLight(Color::Black());

    Logger::LogInfo("Connected controller : {}", gamepad->GetName());
}

void Input::DisconnectGamepad(const u32 id)
{
    GamepadInput* const gamepad = m_Gamepads.FindFirst([id](const GamepadInput& g) { return g.m_Id == id; });

    if (!gamepad)
        return;

    SDL_CloseGamepad(gamepad->m_Handle);
    gamepad->m_Id = 0;
    gamepad->m_Handle = nullptr;
    gamepad->m_IsConnected = false;
    gamepad->m_Battery = -1;
    gamepad->m_BatteryState = GamepadBatteryState::Unknown;
    gamepad->m_Capabilities = GamepadCapabilities::None;
    gamepad->m_Axes.Fill(0.f);
    gamepad->m_Buttons.Fill({});
}

void Input::UpdateGamepadButton(const u32 id, const GamepadButton button, const bool down)
{
    GamepadInput* const gamepad = m_Gamepads.FindFirst([id](const GamepadInput& g) { return g.m_Id == id; });

    if (!gamepad)
        return;

    GamepadButtonStatuses& statuses = gamepad->m_Buttons.At(static_cast<usize>(button));
    const bool wasDown = statuses.At(static_cast<usize>(GamepadButtonStatus::Down));
    const bool wasUp = statuses.At(static_cast<usize>(GamepadButtonStatus::Up));
    if (down)
    {
        if (!wasDown)
        {
            statuses.At(static_cast<usize>(GamepadButtonStatus::Down)) = true;
            statuses.At(static_cast<usize>(GamepadButtonStatus::Up)) = false;
            statuses.At(static_cast<usize>(GamepadButtonStatus::Pressed)) = wasUp;
            statuses.At(static_cast<usize>(GamepadButtonStatus::Released)) = false;
        }
    }
    else
    {
        if (!wasUp)
        {
            statuses.At(static_cast<usize>(GamepadButtonStatus::Down)) = false;
            statuses.At(static_cast<usize>(GamepadButtonStatus::Up)) = true;
            statuses.At(static_cast<usize>(GamepadButtonStatus::Pressed)) = false;
            statuses.At(static_cast<usize>(GamepadButtonStatus::Released)) = wasDown;
        }
    }
}

void Input::UpdateGamepadAxis(const u32 id, const GamepadAxis axis, const s16 value)
{
    GamepadInput* const gamepad = m_Gamepads.FindFirst([id](const GamepadInput& g) { return g.m_Id == id; });

    if (!gamepad)
        return;

    const f32 floatValue = Utils::RemapValue(static_cast<f32>(value), { -32768.f, 32767.f }, { -1, 1 });
    const usize idx = static_cast<usize>(axis);

    gamepad->m_Axes[idx] = Calc::MakeZero(floatValue, GamepadInput::nullAnalogValue);

    if (axis == GamepadAxis::LeftTrigger || axis == GamepadAxis::RightTrigger)
    {
        gamepad->m_Axes[idx] = std::max(0.f, gamepad->m_Axes[idx]);
        const GamepadButton button = static_cast<GamepadButton>(
            idx
            - static_cast<s32>(GamepadAxis::LeftTrigger)
            + static_cast<s32>(GamepadButton::LeftTrigger)
        );

        UpdateGamepadButton(id, button, gamepad->m_Axes[idx] > GamepadInput::nullAnalogValue);
    }
}

void Input::UpdateGamepadBattery(const u32 id, const s8 percent, const GamepadBatteryState state)
{
    GamepadInput* const gamepad = m_Gamepads.FindFirst([id](const GamepadInput& g) { return g.m_Id == id; });

    if (!gamepad)
        return;

    gamepad->m_Battery = percent;
    gamepad->m_BatteryState = state;
}

void Input::UpdateGamepadGyro(u32 id, const Vector3& gyro)
{
    GamepadInput* const gamepad = m_Gamepads.FindFirst([id](const GamepadInput& g) { return g.m_Id == id; });
    if (!gamepad)
        return;

    gamepad->m_Gyroscope = gyro;
}

void Input::UpdateGamepadAccel(u32 id, const Vector3& accel)
{
    GamepadInput* const gamepad = m_Gamepads.FindFirst([id](const GamepadInput& g) { return g.m_Id == id; });
    if (!gamepad)
        return;

    gamepad->m_Accelerometer = accel;
}

void Input::UpdateGamepadTouchpad(const u32 id, const usize touchpad, const usize finger, const Vector2 location)
{
    const GamepadInput* const gamepad = m_Gamepads.FindFirst([id](const GamepadInput& g) { return g.m_Id == id; });
    if (!gamepad)
        return;

    gamepad->m_Touchpads[touchpad].fingerLocations[finger] = location;
}

void Input::Reset()
{
    for (auto& button : m_Mouse)
    {
        button.At(static_cast<usize>(MouseButtonStatus::Pressed)) = false;
        button.At(static_cast<usize>(MouseButtonStatus::Release)) = false;
    }

    m_MouseDelta = Vector2::Zero();
    m_MouseWheel = Vector2::Zero();

    for (auto& key : m_Keyboard)
    {
        key.At(static_cast<usize>(KeyStatus::Pressed)) = false;
        key.At(static_cast<usize>(KeyStatus::Release)) = false;
        key.At(static_cast<usize>(KeyStatus::Repeat)) = false;
    }

    for (auto& gamepad : m_Gamepads)
    {
        for (auto& button : gamepad.m_Buttons)
        {
            button.At(static_cast<usize>(GamepadButtonStatus::Pressed)) = false;
            button.At(static_cast<usize>(GamepadButtonStatus::Released)) = false;
        }
    }
}

Vector2 Input::GetMouseDelta() { return m_MouseDelta; }

Vector2 Input::GetMouseWheel() { return m_MouseWheel; }

void Input::Initialize()
{
    Logger::LogVerbose("Initializing input");

    KeyStatuses defaultKeys;
    defaultKeys.Fill(false);
    m_Keyboard.Fill(defaultKeys);

    MouseStatuses defaultMouseButtons;
    defaultMouseButtons.Fill(false);
    m_Mouse.Fill(defaultMouseButtons);
}
