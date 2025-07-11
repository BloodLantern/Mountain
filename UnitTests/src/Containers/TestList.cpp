// ReSharper disable CppNoDiscardExpression
#include "Common.hpp"

#include <list>

#include <Mountain/Containers/List.hpp>

TEST(Containers_List, DefaultInitialization)
{
    ATTRIBUTE_MAYBE_UNUSED const List<int> defaultInitialized{};
    ATTRIBUTE_MAYBE_UNUSED const std::vector<int> defaultInitializedStd{};

    SUCCEED();
}

TEST(Containers_List, ListInitialization)
{
    ATTRIBUTE_MAYBE_UNUSED const List listInitialized{1, 2, 3};
    ATTRIBUTE_MAYBE_UNUSED const std::vector listInitializedStd{1, 2, 3};

    SUCCEED();
}

TEST(Containers_List, RandomAccess)
{
    const List list{1, 2, 3};
    const std::vector listStd{1, 2, 3};

    EXPECT_EQ(list.GetSize(), listStd.size());
    EXPECT_THROW(list.At(3), ArgumentOutOfRangeException);

    for (size_t i = 0; i < list.GetSize(); ++i)
    {
        EXPECT_EQ(list.At(i), listStd.at(i));
        EXPECT_EQ(list[i], listStd[i]);
    }
}

TEST(Containers_List, Iterator)
{
    List list{1, 2, 3};
    std::vector listStd{1, 2, 3};

    auto it = list.begin();
    auto itStd = listStd.begin();
    for (; it != list.end(); it++, itStd++)
        EXPECT_EQ(*it, *itStd);
}

TEST(Containers_List, Enumerable_Cast)
{
    const List list{1, 2, 3};

    const List fList = list.Cast<float>();

    EXPECT_FLOAT_EQ(fList[0], 1.f);
    EXPECT_FLOAT_EQ(fList[1], 2.f);
    EXPECT_FLOAT_EQ(fList[2], 3.f);
}

TEST(Containers_List, Enumerable_Select)
{
    const List cStrList{"Hello", ", ", "World", "!"};

    const List strList = cStrList.Select([](const char* cStr) { return std::string{cStr}; });

    EXPECT_EQ(strList[0], cStrList[0]);
    EXPECT_EQ(strList[1], cStrList[1]);
    EXPECT_EQ(strList[2], cStrList[2]);
    EXPECT_EQ(strList[3], cStrList[3]);
}
