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

TEST(Containers_List, Enumerable_Average)
{
    const List intList{1, 2, 3, 4, 5};

    const List floatList = intList.Cast<float_t>();

    float_t result1 = intList.Average<>();
    float_t result2 = floatList.Average<>();

    EXPECT_EQ(result1, 3.f);
    EXPECT_EQ(result2, 3.f);
}

TEST(Containers_List, Enumerable_Concat)
{
    const List firstList{1, 2};
    const List secondList{3, 4, 5};

    const List concatList = Concat(firstList, secondList);

    const List resultList{1, 2, 3, 4, 5};

    EXPECT_EQ(concatList[0], resultList[0]);
    EXPECT_EQ(concatList[1], resultList[1]);
    EXPECT_EQ(concatList[2], resultList[2]);
    EXPECT_EQ(concatList[3], resultList[3]);
    EXPECT_EQ(concatList[4], resultList[4]);
}