// ReSharper disable CppNoDiscardExpression
#include "Common.hpp"

#include <array>

#include "Mountain/Containers/Array.hpp"
#include "Mountain/Containers/List.hpp"

using namespace Mountain;

TEST(Array, DefaultInitialization)
{
    ATTRIBUTE_MAYBE_UNUSED constexpr Array<int, 3> defaultInitialized{};
    ATTRIBUTE_MAYBE_UNUSED constexpr std::array<int, 3> defaultInitializedStd{};

    SUCCEED();
}

TEST(Array, ListInitialization)
{
    ATTRIBUTE_MAYBE_UNUSED constexpr Array listInitialized{1, 2, 3};
    ATTRIBUTE_MAYBE_UNUSED constexpr std::array listInitializedStd{1, 2, 3};

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
