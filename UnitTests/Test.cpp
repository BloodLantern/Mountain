// ReSharper disable CppNoDiscardExpression
#include <array>

#include <gtest/gtest.h>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"

using namespace Mountain;

TEST(Array, DefaultInitialization)
{
    Array<int, 3> defaultInitialized;
    std::array<int, 3> defaultInitializedStd;

    EXPECT_EQ(defaultInitialized.GetSize(), defaultInitializedStd.size());
    EXPECT_THROW(defaultInitialized.At(3), ArgumentOutOfRangeException);
    EXPECT_EQ(defaultInitialized.At(1), defaultInitializedStd.at(1));
    EXPECT_EQ(defaultInitialized[1], defaultInitializedStd[1]);
}

TEST(Array, ListInitialization)
{
    Array listInitialized{1, 2, 3};
    std::array listInitializedStd{1, 2, 3};

    EXPECT_EQ(listInitialized.GetSize(), listInitializedStd.size());
    EXPECT_THROW(listInitialized.At(3), ArgumentOutOfRangeException);
    EXPECT_EQ(listInitialized.At(1), listInitializedStd.at(1));
    EXPECT_EQ(listInitialized[1], listInitializedStd[1]);
}

// TODO - Unit tests
