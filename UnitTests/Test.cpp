// ReSharper disable CppNoDiscardExpression
#include <array>

#include <gtest/gtest.h>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"

using namespace Mountain;

TEST(Array, DefaultInitialization)
{
    constexpr Array<int, 3> defaultInitialized{};
    constexpr std::array<int, 3> defaultInitializedStd{};

    EXPECT_EQ(defaultInitialized, defaultInitializedStd);
}

TEST(Array, ListInitialization)
{
    constexpr Array listInitialized{1, 2, 3};
    constexpr std::array listInitializedStd{1, 2, 3};

    EXPECT_EQ(listInitialized, listInitializedStd);
}

TEST(Array, RandomAccess)
{
    constexpr Array array{1, 2, 3};
    constexpr std::array arrayStd{1, 2, 3};

    EXPECT_EQ(array.GetSize(), arrayStd.size());
    EXPECT_THROW(array.At(3), ArgumentOutOfRangeException);

    for (int i = 0; i < array.GetSize(); ++i)
    {
        EXPECT_EQ(array.At(i), arrayStd.at(i));
        EXPECT_EQ(array[i], arrayStd[i]);
    }
}

TEST(Array, Iterator)
{
    constexpr Array array{1, 2, 3};
    constexpr std::array arrayStd{1, 2, 3};

    auto it = array.begin();
    auto itStd = arrayStd.begin();
    for (; it != array.end(); it++, itStd++)
        EXPECT_EQ(*it, *itStd);
}

// TODO - Unit tests
