#include "Common.hpp"

#include <Mountain/Utils/Utils.hpp>

TEST(Utils_Utils, IntToPointer)
{
    EXPECT_EQ(Utils::IntToPointer<void>(0), nullptr);
}

TEST(Utils_Utils, PointerToInt)
{
    EXPECT_EQ(Utils::PointerToInt(nullptr), 0);
}

TEST(Utils_Utils, HumanizeString)
{
    EXPECT_EQ(Utils::HumanizeString("stringToHumanize"), "String To Humanize");
    EXPECT_EQ(Utils::HumanizeString("RequiresUIReload"), "Requires UI Reload");
}

TEST(Utils_Utils, RemapValue)
{
    EXPECT_FLOAT_EQ(Utils::RemapValue(5.f, 0.f, 10.f, 0.f, 1.f), 0.5f);
    EXPECT_EQ(Utils::RemapValue(5ull, 0ull, 10ull, 0ull, 2ull), 1ull);
}

TEST(Utils_Utils, NormalizeAngle)
{
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(0.f), 0.f);
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(Calc::TwoPi), Calc::TwoPi);

    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(Calc::Pi * 3.f), Calc::Pi);
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(5.f * Calc::PiOver2), Calc::PiOver2);

    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(-Calc::Pi), Calc::Pi);
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(-Calc::PiOver2), 3.f * Calc::PiOver2);
}

TEST(Utils_Utils, DynamicPointerCast)
{
    struct A
    {
        int32_t i = 1;

        A() = default;

        explicit A(const int32_t i) : i(i) {}

        virtual ~A() = default;

        DEFAULT_COPY_MOVE_OPERATIONS(A)
    };

    struct B : A
    {
        B() : A(2) {}
    };

    Pointer<B> b = Pointer<B>::New();
    EXPECT_EQ(b->i, 2);

    const Pointer<A> a = Utils::DynamicPointerCast<A>(b);
    EXPECT_EQ(a->i, 2);

    b = Utils::DynamicPointerCast<B>(Pointer<A>::New());
    EXPECT_FALSE(b.IsValid());
}

TEST(Utils_Utils, ArrayContains)
{
    constexpr std::array array{1, 2, 3};

    EXPECT_TRUE(Utils::ArrayContains(array, 2));
    EXPECT_FALSE(Utils::ArrayContains(array, 4));
}
