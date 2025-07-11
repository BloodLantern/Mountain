#include "Common.hpp"

#include <array>

#include "Mountain/Containers/Array.hpp"
#include "Mountain/Containers/List.hpp"

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
