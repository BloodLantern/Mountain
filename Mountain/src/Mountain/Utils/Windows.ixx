module;

#include "Mountain/Core.hpp"

export module Mountain.Utils:Windows;

import std;
import Mountain.Core;

export namespace Mountain::Windows
{
    MOUNTAIN_API bool_t CheckError();

    MOUNTAIN_API void SilenceError();

    MOUNTAIN_API std::string GetAppdataLocalPath();

    MOUNTAIN_API std::string GetAppdataRoamingPath();
}
