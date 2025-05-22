export module Mountain:Utils_Windows;

import "Mountain/Core.hpp";

import std;
export import :Core;

export namespace Mountain::Windows
{
    MOUNTAIN_API bool_t CheckError();

    MOUNTAIN_API void SilenceError();

    MOUNTAIN_API std::string GetAppdataLocalPath();

    MOUNTAIN_API std::string GetAppdataRoamingPath();
}
