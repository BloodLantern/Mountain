#include "PrecompiledHeader.hpp"

#include <Mountain/Utils/Guid.hpp>

TEST(Utils_Guid, New)
{
    const Guid a = Guid::New(), b = Guid::New();

    EXPECT_NE(a, b);
    EXPECT_NE(a, Guid::Empty());
    EXPECT_EQ(a, a);
    EXPECT_EQ(Guid::Empty(), Guid::Empty());
    EXPECT_NE(a != b, false);
}

TEST(Utils_Guid, DataAccess)
{
    const Guid a = Guid::FromString("01234567-89AB-CDEF-01-23-45-67-89-AB-CD-EF");

    EXPECT_EQ(a.GetData1(), 0x01234567);
    EXPECT_EQ(a.GetData2(), 0x89AB);
    EXPECT_EQ(a.GetData3(), 0xCDEF);

    const auto& data4 = a.GetData4();
    EXPECT_EQ(data4[0], 0x01);
    EXPECT_EQ(data4[7], 0xEF);
}

TEST(Utils_Guid, StringConversions)
{
    constexpr const c8* str = "FFFFFFFF-EEEE-DDDD-CC-BB-AA-99-88-77-66-55";
    const Guid guid = Guid::FromString(str);

    EXPECT_EQ(guid.ToString(), str);
}

TEST(Utils_Guid, HashCode)
{
    const Guid guid = Guid::New();

    EXPECT_EQ(guid.GetHashCode(), guid.GetHashCode());
    EXPECT_NE(guid.GetHashCode(), Guid::New().GetHashCode());
}
