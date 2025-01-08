#include "Mountain/utils/stopwatch.hpp"

using namespace Mountain;

Stopwatch::Stopwatch()
    : m_Start(std::chrono::high_resolution_clock::now())
{
}

float_t Stopwatch::GetElapsedSeconds() const
{
    return std::chrono::duration_cast<std::chrono::duration<float_t>>(std::chrono::high_resolution_clock::now() - m_Start).count();
}
