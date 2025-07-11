// ReSharper disable CppNoDiscardExpression
#include "Common.hpp"

#include <array>

#include <Mountain/Containers/Array.hpp>

TEST(Containers_Array, DefaultInitialization)
{
    ATTRIBUTE_MAYBE_UNUSED constexpr Array<int, 3> defaultInitialized{};
    ATTRIBUTE_MAYBE_UNUSED constexpr std::array<int, 3> defaultInitializedStd{};

    SUCCEED();
}

TEST(Containers_Array, ListInitialization)
{
    ATTRIBUTE_MAYBE_UNUSED constexpr Array listInitialized{1, 2, 3};
    ATTRIBUTE_MAYBE_UNUSED constexpr std::array listInitializedStd{1, 2, 3};

    SUCCEED();
}

TEST(Containers_Array, RandomAccess)
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

TEST(Containers_Array, Iterator)
{
    constexpr Array array{1, 2, 3};
    constexpr std::array arrayStd{1, 2, 3};

    auto it = array.begin();
    auto itStd = arrayStd.begin();
    for (; it != array.end(); it++, itStd++)
        EXPECT_EQ(*it, *itStd);
}

TEST(Containers_Array, Enumerable_Cast)
{
    constexpr Array array{1, 2, 3};

    const Array fArray = array.Cast<float>();

    EXPECT_FLOAT_EQ(fArray[0], 1.f);
    EXPECT_FLOAT_EQ(fArray[1], 2.f);
    EXPECT_FLOAT_EQ(fArray[2], 3.f);
}

TEST(Containers_Array, Enumerable_Select)
{
    constexpr Array cStrArray{"Hello", ", ", "World", "!"};

    const Array strArray = cStrArray.Select([](const char* cStr) { return std::string{cStr}; });

    EXPECT_EQ(strArray[0], cStrArray[0]);
    EXPECT_EQ(strArray[1], cStrArray[1]);
    EXPECT_EQ(strArray[2], cStrArray[2]);
    EXPECT_EQ(strArray[3], cStrArray[3]);
}
