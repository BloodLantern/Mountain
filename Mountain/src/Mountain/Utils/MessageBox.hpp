#pragma once

#include "Mountain/Core.hpp"

/// @file MessageBox.hpp
/// @brief Defines the MessageBox namespace containing utility functions to inform the user of something while blocking the program execution.

/// @brief Defines functions to work with MessageBox dialog utilities.
namespace Mountain::MessageBox
{
    /// @brief Popup icon for the MessageBox functions.
    enum class Type : u8
    {
        /// @brief Shows an <i>i</i> in a circle.
        Information,
        /// @brief Shows an exclamation mark in a triangle.
        Warning,
        /// @brief Shows a stop sign.
        Error,
    };

    /// @brief Result of the MessageBox functions.
    /// @note The values are declared as flags, but this is only for convenience in how they are used internally.
    /// You should always expect to receive a single value of this enum.
    enum class Result : u8
    {
        /// @brief The user pressed the Ok button.
        Ok = 1 << 0,
        /// @brief The user pressed the Cancel button.
        Cancel = 1 << 1,
        /// @brief The user pressed the Yes button.
        Yes = 1 << 2,
        /// @brief The user pressed the No button.
        No = 1 << 3,
        /// @brief The user pressed the Retry button.
        Retry = 1 << 4,
        /// @brief The user pressed the Try Again button.
        TryAgain = 1 << 5,
        /// @brief The user pressed the Continue button.
        Continue = 1 << 6,
        /// @brief The user closed the popup.
        Close = 1 << 7
    };

    constexpr u16 ButtonConfigurationButtonCountBitOffset = 14;
    constexpr u16 ButtonConfigurationButtonCountMask = 0b11 << ButtonConfigurationButtonCountBitOffset;
    constexpr u16 ButtonConfigurationButtonCountOne = 1 << ButtonConfigurationButtonCountBitOffset;
    constexpr u16 ButtonConfigurationButtonCountTwo = 2 << ButtonConfigurationButtonCountBitOffset;
    constexpr u16 ButtonConfigurationButtonCountThree = 3 << ButtonConfigurationButtonCountBitOffset;

    /// @brief Options for the MessageBox functions.
    enum class ButtonConfiguration : u16
    {
        /// @brief The MessageBox contains the single option Ok.
        Ok = static_cast<int>(Result::Ok) | ButtonConfigurationButtonCountOne,
        /// @brief The MessageBox contains the options Ok, Cancel.
        OkCancel = static_cast<int>(Result::Ok) | static_cast<int>(Result::Cancel) | ButtonConfigurationButtonCountTwo,
        /// @brief The MessageBox contains the options Yes, No, Cancel.
        YesNoCancel = static_cast<int>(Result::Yes) | static_cast<int>(Result::No) | static_cast<int>(Result::Cancel) | ButtonConfigurationButtonCountThree,
        /// @brief The MessageBox contains the options Yes, No.
        YesNo = static_cast<int>(Result::Yes) | static_cast<int>(Result::No) | ButtonConfigurationButtonCountTwo,
        /// @brief The MessageBox contains the options Retry, Cancel.
        RetryCancel = static_cast<int>(Result::Retry) | static_cast<int>(Result::Cancel) | ButtonConfigurationButtonCountTwo,
        /// @brief The MessageBox contains the options Cancel, Try Again, Continue.
        CancelTryAgainContinue = static_cast<int>(Result::Cancel) | static_cast<int>(Result::TryAgain) | static_cast<int>(Result::Continue) | ButtonConfigurationButtonCountThree
    };

    /// @brief Shows a MessageBox dialog with the given options.
    /// @note This function doesn't return until the dialog is closed or a button is pressed on the dialog.
    Result Show(const c8* title, const c8* text, ButtonConfiguration buttonConfiguration = ButtonConfiguration::Ok, Type type = Type::Information);
}
