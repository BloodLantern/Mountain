export module Mountain:Core_Types;

import std;

export import Math;

export namespace Mountain {}

export using nullptr_t = decltype(nullptr);

export using Action = std::function<void()>;
