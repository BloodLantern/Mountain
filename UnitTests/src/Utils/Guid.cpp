#include "Common.hpp"

#include <Mountain/Utils/Guid.hpp>

TEST(Utils_Guid, New)
{
    const Guid a = Guid::New(), b = Guid::New();

    EXPECT_NE(a, b);
    EXPECT_NE(a, Guid::Empty());
    EXPECT_EQ(a, a);
    EXPECT_EQ(Guid::Empty(), Guid::Empty());
}

TEST(Utils_Guid, StringConversions)
{
    constexpr const char_t* str = "FFFFFFFF-EEEE-DDDD-CC-BB-AA-99-88-77-66-55";
    const Guid guid = Guid::FromString(str);

    EXPECT_EQ(guid.ToString(), str);
}

TEST(Utils_Guid, HashCode)
{
    const Guid guid = Guid::New();

    EXPECT_EQ(guid.GetHashCode(), guid.GetHashCode());
    EXPECT_NE(guid.GetHashCode(), Guid::New().GetHashCode());
}
