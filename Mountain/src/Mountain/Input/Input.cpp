#include "Mountain/Input/Input.hpp"

#include "Time.hpp"
#include "Mountain/Utils/Logger.hpp"
#include "SDL3/SDL_gamepad.h"

using namespace Mountain;

bool_t Input::GetKey(const Key key, const KeyStatus status)
{
    return m_Keyboard.At(static_cast<size_t>(key)).At(static_cast<size_t>(status));
}

bool_t Input::GetMouseButton(const MouseButton mouseButton, const MouseButtonStatus status)
{
    return m_Mouse.At(static_cast<size_t>(mouseButton)).At(static_cast<size_t>(status));
}

const GamepadInput& Input::GetGamepad(const uint32_t gamepadId)
{
    if (gamepadId > GamepadMax)
    {
        Logger::LogError("Invalid gamepad ID {}", gamepadId);
        THROW(ArgumentException{"Invalid gamepad ID", "gamepadId"});
    }

    return m_Gamepads.At(gamepadId);
}

uint32_t Input::GetGamepadsConnected()
{
    return static_cast<uint32_t>(std::ranges::count_if(m_Gamepads, [](auto&& gamepad) -> bool_t { return gamepad.m_IsConnected; }));
}

bool_t Input::IsGamepadConnected(const uint32_t index) { return m_Gamepads[index].m_IsConnected; }

Vector2 Input::GetMousePosition() { return m_MousePosition; }

void Input::HandleKeyboard(const size_t key, const KeyAction action)
{
    if (key > m_Keyboard.GetSize())
        return;

    KeyStatuses& keyStatuses = m_Keyboard.At(key);

    switch (action)
    {
        case KeyAction::Release:
            keyStatuses.At(static_cast<size_t>(KeyStatus::Down)) = false;
            keyStatuses.At(static_cast<size_t>(KeyStatus::Release)) = true;
            keyStatuses.At(static_cast<size_t>(KeyStatus::Repeat)) = false;
            break;

        case KeyAction::Press:
            keyStatuses.At(static_cast<size_t>(KeyStatus::Pressed)) = true;
            keyStatuses.At(static_cast<size_t>(KeyStatus::Down)) = true;
            break;

        case KeyAction::Repeat:
            keyStatuses.At(static_cast<size_t>(KeyStatus::Repeat)) = true;
            break;
    }
}

void Input::HandleMouseButton(const size_t mouseButton, const bool_t pressed)
{
    MouseStatuses& keyStatuses = m_Mouse.At(mouseButton);

    if (pressed)
    {
        keyStatuses.At(static_cast<size_t>(MouseButtonStatus::Pressed)) = true;
        keyStatuses.At(static_cast<size_t>(MouseButtonStatus::Down)) = true;
    }
    else
    {
        keyStatuses.At(static_cast<size_t>(MouseButtonStatus::Down)) = false;
        keyStatuses.At(static_cast<size_t>(MouseButtonStatus::Release)) = true;
    }
}

void Input::HandleMouseMovement(const Vector2 newPosition)
{
    m_LastMousePosition = m_MousePosition;

    m_MousePosition = newPosition;
    m_MouseDelta = m_MousePosition - m_LastMousePosition;
}

void Input::HandleMouseWheel(const int32_t wheelX, const int32_t wheelY)
{
    m_MouseWheel += { static_cast<float_t>(wheelX), static_cast<float_t>(wheelY) };
}

void Input::ConnectGamepad(const uint32_t id)
{
    if (id == 0)
        return;

    GamepadInput* gamepad = FindFirst(m_Gamepads, [](const GamepadInput& g) { return !g.m_IsConnected; });

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

    const int32_t nbrTouchpads = SDL_GetNumGamepadTouchpads(gamepad->m_Handle);
    if (nbrTouchpads != 0)
    {
        capabilities |= GamepadCapabilities::Touchpad;
        gamepad->m_Touchpads.Resize(nbrTouchpads);

        for (int32_t i = 0; i < nbrTouchpads; i++)
        {
            gamepad->m_Touchpads[i].nbrOfFingersMax = static_cast<uint8_t>(SDL_GetNumGamepadTouchpadFingers(gamepad->m_Handle, i));
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

void Input::DisconnectGamepad(const uint32_t id)
{
    GamepadInput* gamepad = FindFirst(m_Gamepads, [id](const GamepadInput& g) { return g.m_Id == id; });

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

void Input::UpdateGamepadBattery(const uint32_t id, const int8_t percent, const GamepadBatteryState state)
{
    GamepadInput* const gamepad = FindFirst(m_Gamepads, [id](const GamepadInput& g) { return g.m_Id == id; });
    if (!gamepad)
        return;
    
    gamepad->m_Battery = percent;
    gamepad->m_BatteryState = state;
}

void Input::UpdateGamepadGyro(uint32_t id, const Vector3& gyro)
{
    GamepadInput* const gamepad = FindFirst(m_Gamepads, [id](const GamepadInput& g) { return g.m_Id == id; });
    if (!gamepad)
        return;
    
    gamepad->m_Gyroscope = gyro;
}

void Input::UpdateGamepadAccel(uint32_t id, const Vector3& accel)
{
    GamepadInput* const gamepad = FindFirst(m_Gamepads, [id](const GamepadInput& g) { return g.m_Id == id; });
    if (!gamepad)
        return;
    
    gamepad->m_Accelerometer = accel;
}

void Input::UpdateGamepadTouchpad(const uint32_t id, const size_t touchpad, const size_t finger, const Vector2 location)
{
    const GamepadInput* const gamepad = FindFirst(m_Gamepads, [id](const GamepadInput& g) { return g.m_Id == id; });
    if (!gamepad)
        return;
    
    gamepad->m_Touchpads[touchpad].fingerLocations[finger] = location;
}

void Input::UpdateGamepads()
{
    for (uint32_t i = 0; i < GamepadMax; i++)
    {
        GamepadInput& gamepad = m_Gamepads[i];

        if (!gamepad.m_IsConnected)
            continue;

        for (uint32_t k = 0; k < magic_enum::enum_count<GamepadAxis>(); k++)
        {
            const uint16_t value = SDL_GetGamepadAxis(gamepad.m_Handle, static_cast<SDL_GamepadAxis>(k));
            const float_t floatValue = Utils::RemapValue(static_cast<float_t>(value), { -32768.f, 32767.f }, { -1, 1 });

            gamepad.m_Axes[k] = Calc::MakeZero(floatValue, GamepadInput::nullAnalogValue);

            const GamepadAxis axis = static_cast<GamepadAxis>(k);
            if (axis == GamepadAxis::LeftTrigger || axis == GamepadAxis::RightTrigger)
                gamepad.m_Axes[k] = std::max(0.f, gamepad.m_Axes[k]);
        }

        for (uint32_t k = 0; k < magic_enum::enum_count<GamepadButton>(); k++)
        {
            GamepadButtonStatuses& statuses = gamepad.m_Buttons.At(k);
            const bool_t wasDown = statuses.At(static_cast<size_t>(GamepadButtonStatus::Down));
            const bool_t wasUp = statuses.At(static_cast<size_t>(GamepadButtonStatus::Up));

            if (k < magic_enum::enum_count<SDL_GamepadButton>())
            {
                if (SDL_GetGamepadButton(gamepad.m_Handle, static_cast<SDL_GamepadButton>(k)))
                {
                    if (!wasDown)
                    {
                        statuses.At(static_cast<size_t>(GamepadButtonStatus::Down)) = true;
                        statuses.At(static_cast<size_t>(GamepadButtonStatus::Up)) = false;
                        statuses.At(static_cast<size_t>(GamepadButtonStatus::Pressed)) = wasUp;
                        statuses.At(static_cast<size_t>(GamepadButtonStatus::Released)) = false;
                    }
                }
                else
                {
                    if (!wasUp)
                    {
                        statuses.At(static_cast<size_t>(GamepadButtonStatus::Down)) = false;
                        statuses.At(static_cast<size_t>(GamepadButtonStatus::Up)) = true;
                        statuses.At(static_cast<size_t>(GamepadButtonStatus::Pressed)) = false;
                        statuses.At(static_cast<size_t>(GamepadButtonStatus::Released)) = wasDown;
                    }
                }
            }
            else if (static_cast<GamepadButton>(k) == GamepadButton::LeftTrigger || static_cast<GamepadButton>(k) == GamepadButton::RightTrigger)
            {
                // Mountain extensions
                const GamepadAxis trigger = static_cast<GamepadAxis>(
                        k
                        - static_cast<int32_t>(GamepadButton::LeftTrigger)
                        + static_cast<int32_t>(GamepadAxis::LeftTrigger)
                    );

                const bool_t release = gamepad.m_Axes[static_cast<size_t>(trigger)] < GamepadInput::nullAnalogValue;

                if (release)
                {
                    statuses.At(static_cast<size_t>(GamepadButtonStatus::Down)) = false;
                    statuses.At(static_cast<size_t>(GamepadButtonStatus::Up)) = true;
                    statuses.At(static_cast<size_t>(GamepadButtonStatus::Pressed)) = false;
                    statuses.At(static_cast<size_t>(GamepadButtonStatus::Released)) = wasDown;
                }
                else
                {

                    statuses.At(static_cast<size_t>(GamepadButtonStatus::Down)) = true;
                    statuses.At(static_cast<size_t>(GamepadButtonStatus::Up)) = false;
                    statuses.At(static_cast<size_t>(GamepadButtonStatus::Pressed)) = wasUp;
                    statuses.At(static_cast<size_t>(GamepadButtonStatus::Released)) = false;
                }
            }
        }
    }
}

void Input::Update()
{
    UpdateGamepads();
}

void Input::Reset()
{
    for (auto& button : m_Mouse)
    {
        button.At(static_cast<size_t>(MouseButtonStatus::Pressed)) = false;
        button.At(static_cast<size_t>(MouseButtonStatus::Release)) = false;
    }

    m_MouseWheel = Vector2::Zero();

    for (auto& key : m_Keyboard)
    {
        key.At(static_cast<size_t>(KeyStatus::Pressed)) = false;
        key.At(static_cast<size_t>(KeyStatus::Release)) = false;
        key.At(static_cast<size_t>(KeyStatus::Repeat)) = false;
    }

    for (auto& gamepad : m_Gamepads)
    {
        for (auto& button : gamepad.m_Buttons)
        {
            button.At(static_cast<size_t>(GamepadButtonStatus::Pressed)) = false;
            button.At(static_cast<size_t>(GamepadButtonStatus::Released)) = false;
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
