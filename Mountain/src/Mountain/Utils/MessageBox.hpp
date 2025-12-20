#pragma once

#include <string>

#include "Mountain/Core.hpp"

/// @file MessageBox.hpp
/// @brief Defines the MessageBox namespace containing utility functions to inform the user of something while blocking the program execution.

namespace Mountain
{
    /// @brief Defines functions to work with Windows MessageBox utilities.
    class MessageBox
    {
        STATIC_CLASS(MessageBox)

    public:
        /// @brief Options for the MessageBox functions.
        enum class Type
        {
            /// @brief The MessageBox contains the single option Ok.
            Ok,
            /// @brief The MessageBox contains the options Ok, Cancel.
            OkCancel,
            /// @brief The MessageBox contains the options Yes, No, Cancel.
            YesNoCancel,
            /// @brief The MessageBox contains the options Yes, No.
            YesNo,
            /// @brief The MessageBox contains the options Retry, Cancel.
            RetryCancel,
            /// @brief The MessageBox contains the options Cancel, Try Again, Continue.
            CancelTryContinue
        };

        /// @brief Popup icon for the MessageBox functions.
        enum class Icon
        {
            /// @brief No specific icon.
            None,

            /// @brief Shows an exclamation mark in a triangle.
            Warning,
            /// @brief Shows a stop sign.
            Error,
            /// @brief Shows an <i>i</i> in a circle.
            Information,
        };

        /// @brief Default selected button for the MessageBox functions.
        enum class DefaultButton
        {
            /// @brief Sets the default button as the first one.
            First,
            /// @brief Sets the default button as the second one.
            Second,
            /// @brief Sets the default button as the third one.
            Third,
        };

        /// @brief Result of the MessageBox functions.
        enum class Result
        {
            /// @brief The user pressed the Ok button.
            Ok,
            /// @brief The user pressed the Cancel button.
            Cancel,
            /// @brief The user pressed the Yes button.
            Yes,
            /// @brief The user pressed the No button.
            No,
            /// @brief The user pressed the Retry button.
            Retry,
            /// @brief The user pressed the Try Again button.
            Try,
            /// @brief The user pressed the Continue button.
            Continue,
            /// @brief The user closed the popup.
            Close
        };

        /// @brief Shows a MessageBox with the given options.
        static Result Show(const c8* title, const c8* text, Type type, Icon icon = Icon::None, DefaultButton defaultButton = DefaultButton::First);

    private:
        static u32 TypeToWindows(Type type);

        static u32 IconToWindows(Icon icon);

        static u32 DefaultButtonToWindows(DefaultButton defaultButton);

        static Result ParseResult(s32 windowsResult);

        static Result Call(
            const c8* text,
            const c8* title,
            Type type,
            Icon icon,
            DefaultButton defaultButton
        );
    };
}
