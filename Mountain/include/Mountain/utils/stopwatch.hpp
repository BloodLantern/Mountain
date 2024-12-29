#pragma once

#include <chrono>

#include "Mountain/core.hpp"

namespace Mountain
{
    class Stopwatch
    {
    public:
        /// @brief Starts a new stopwatch
        Stopwatch();

        [[nodiscard]]
        float_t GetElapsedSeconds() const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };
}
