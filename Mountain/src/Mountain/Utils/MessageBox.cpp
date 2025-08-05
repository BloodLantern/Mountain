#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/MessageBox.hpp"

#include <stdexcept>

#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

MessageBox::Result MessageBox::Show(const char_t* title, const char_t* text, const Type type, const Icon icon, const DefaultButton defaultButton)
{
    return Call(text, title, type, icon, defaultButton);
}

uint32_t MessageBox::TypeToWindows(const Type type)
{
    switch (type)
    {
        case Type::Ok: return MB_OK;
        case Type::OkCancel: return MB_OKCANCEL;
        case Type::YesNoCancel: return MB_YESNOCANCEL;
        case Type::YesNo: return MB_YESNO;
        case Type::RetryCancel: return MB_RETRYCANCEL;
        case Type::CancelTryContinue: return MB_CANCELTRYCONTINUE;
    }

    THROW(ArgumentOutOfRangeException{"Invalid MessageBox type", "type"});
}

uint32_t MessageBox::IconToWindows(const Icon icon)
{
    switch (icon)
    {
        case Icon::None: return 0;
        case Icon::Warning: return MB_ICONWARNING;
        case Icon::Error: return MB_ICONERROR;
        case Icon::Information: return MB_ICONINFORMATION;
    }

    THROW(ArgumentOutOfRangeException{"Invalid MessageBox icon", "icon"});
}

uint32_t MessageBox::DefaultButtonToWindows(const DefaultButton defaultButton)
{
    switch (defaultButton)
    {
        case DefaultButton::First: return MB_DEFBUTTON1;
        case DefaultButton::Second: return MB_DEFBUTTON2;
        case DefaultButton::Third: return MB_DEFBUTTON3;
    }

    THROW(ArgumentOutOfRangeException{"Invalid MessageBox default button", "defaultButton"});
}

MessageBox::Result MessageBox::ParseResult(const int32_t windowsResult)
{
    switch (windowsResult)
    {
        case IDOK: return Result::Ok;
        case IDCANCEL: return Result::Cancel;
        case IDRETRY: return Result::Retry;
        case IDYES: return Result::Yes;
        case IDNO: return Result::No;
        case IDCLOSE: return Result::Close;
        case IDTRYAGAIN: return Result::Try;
        case IDCONTINUE: return Result::Continue;

        default: THROW(ArgumentOutOfRangeException{"Invalid MessageBox result", "windowsResult"});
    }
}

MessageBox::Result MessageBox::Call(const char_t* const text, const char_t* const title, const Type type, const Icon icon, const DefaultButton defaultButton)
{
    const Result result = ParseResult(MessageBoxA(nullptr, text, title, TypeToWindows(type) | IconToWindows(icon) | DefaultButtonToWindows(defaultButton)));
    Windows::CheckError();
    return result;
}
