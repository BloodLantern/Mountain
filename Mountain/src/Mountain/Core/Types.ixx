export module Mountain:Core_Types;

import std;

export import Math;

export
{
    namespace Mountain {}

    using nullptr_t = decltype(nullptr);

    using Action = std::function<void()>;
}
