// ReSharper disable CppNoDiscardExpression
#include <array>

#include <gtest/gtest.h>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Containers/List.hpp"

using namespace Mountain;

#pragma warning(push)
#pragma warning(disable: 4834) // discarding return value of function with 'nodiscard' attribute
#pragma warning(disable: 4723) // potential divide by 0

TEST(Array, DefaultInitialization)
{
    [[maybe_unused]] constexpr Array<int, 3> defaultInitialized{};
    [[maybe_unused]] constexpr std::array<int, 3> defaultInitializedStd{};

    SUCCEED();
}

TEST(Array, ListInitialization)
{
    [[maybe_unused]] constexpr Array listInitialized{1, 2, 3};
    [[maybe_unused]] constexpr std::array listInitializedStd{1, 2, 3};

    SUCCEED();
}

TEST(Array, RandomAccess)
{
    constexpr Array array{1, 2, 3};
    constexpr std::array arrayStd{1, 2, 3};

    EXPECT_EQ(array.GetSize(), arrayStd.size());
    EXPECT_THROW(array.At(3), ArgumentOutOfRangeException);

    for (size_t i = 0; i < array.GetSize(); ++i)
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

TEST(List, DefaultInitialization)
{
    List<int> defaultInitialized{};
    std::vector<int> defaultInitializedStd{};

    //EXPECT_EQ(defaultInitialized, defaultInitializedStd);
}

TEST(List, ListInitialization)
{
    List listInitialized{1, 2, 3};
    std::vector listInitializedStd{1, 2, 3};

    //EXPECT_EQ(listInitialized, listInitializedStd);
}

// TODO - Unit tests

#pragma warning(pop)
