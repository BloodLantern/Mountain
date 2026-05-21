#include "Mountain/Utils/MessageBox.hpp"

#include <SDL3/SDL_messagebox.h>

#include "Mountain/Window.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"

using namespace Mountain;

namespace
{
    using namespace MessageBox;

    SDL_MessageBoxFlags TypeToSdl(const Type type)
    {
        switch (type)
        {
            case Type::Information: return SDL_MESSAGEBOX_INFORMATION;
            case Type::Warning: return SDL_MESSAGEBOX_WARNING;
            case Type::Error: return SDL_MESSAGEBOX_ERROR;
        }

        THROW(ArgumentOutOfRangeException{"Invalid MessageBox type", "type"});
    }

    SDL_MessageBoxButtonData SetupButtonData(const Result value, const SDL_MessageBoxButtonFlags flags = 0)
    {
        return {
            .flags = flags,
            .buttonID = static_cast<int>(value),
            .text = magic_enum::enum_name(value).data()
        };
    }

    void SetupButtons(const List<SDL_MessageBoxButtonData>& buttonDatas, const ButtonConfiguration buttonConfiguration)
    {
        switch (buttonConfiguration)
        {
            case ButtonConfiguration::Ok:
                buttonDatas[0] = SetupButtonData(Result::Ok, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT | SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);
                break;
            case ButtonConfiguration::OkCancel:
                buttonDatas[0] = SetupButtonData(Result::Ok, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
                buttonDatas[1] = SetupButtonData(Result::Cancel, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);
                break;
            case ButtonConfiguration::YesNoCancel:
                buttonDatas[0] = SetupButtonData(Result::Yes, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
                buttonDatas[1] = SetupButtonData(Result::No);
                buttonDatas[2] = SetupButtonData(Result::Cancel, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);
                break;
            case ButtonConfiguration::YesNo:
                buttonDatas[0] = SetupButtonData(Result::Yes, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
                buttonDatas[1] = SetupButtonData(Result::No, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);
                break;
            case ButtonConfiguration::RetryCancel:
                buttonDatas[0] = SetupButtonData(Result::Retry, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
                buttonDatas[1] = SetupButtonData(Result::Cancel, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);
                break;
            case ButtonConfiguration::CancelTryAgainContinue:
                buttonDatas[0] = SetupButtonData(Result::Cancel, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);
                buttonDatas[1] = SetupButtonData(Result::TryAgain, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
                buttonDatas[2] = SetupButtonData(Result::Continue);
                break;
        }
    }
}

Result MessageBox::Show(const c8* title, const c8* text, const ButtonConfiguration buttonConfiguration, const Type type)
{
    const usize buttonCount = (static_cast<u16>(buttonConfiguration) & ButtonConfigurationButtonCountMask) >> ButtonConfigurationButtonCountBitOffset;
    const List<SDL_MessageBoxButtonData> buttonDatas{buttonCount};

    SetupButtons(buttonDatas, buttonConfiguration);

    const SDL_MessageBoxData data{
        .flags = TypeToSdl(type),
        .window = Window::GetSdlHandle(),
        .title = title,
        .message = text,
        .numbuttons = static_cast<int>(buttonDatas.GetSize()),
        .buttons = buttonDatas.GetData(),
        .colorScheme = nullptr
    };

    int hitButtonId = 0;
    if (!SDL_ShowMessageBox(&data, &hitButtonId))
    {
        Logger::LogError("SDL failed to show MessageBox");
        return Result::Close;
    }

    return static_cast<Result>(hitButtonId);
}
