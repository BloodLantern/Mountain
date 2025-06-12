#include <array>

#include <gtest/gtest.h>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"

using namespace Mountain;

template <typename T, size_t Size>
struct Test
{
    T array[Size];
};

constexpr bool b = std::is_aggregate_v<Array<int, 3>>;

TEST(Array, Initialization)
{
    Array<int, 3> defaultInitialized;
    Array listInitialized{1, 2, 3};
    std::array a{1, 2, 3};
    ::Test t{1, 2, 3};
}

// TODO - Unit tests
