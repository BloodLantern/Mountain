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

TEST(Utils_Utils, HumanizeVariableName)
{
    EXPECT_EQ(Utils::HumanizeVariableName("m_Variable"), "Variable");
    EXPECT_EQ(Utils::HumanizeVariableName("m_variableName"), "Variable Name");
    EXPECT_EQ(Utils::HumanizeVariableName("variable"), "Variable");
}

TEST(Utils_Utils, RemapValue)
{
    EXPECT_FLOAT_EQ(Utils::RemapValue(5.f, 0.f, 10.f, 0.f, 1.f), 0.5f);
    EXPECT_EQ(Utils::RemapValue(5ull, 0ull, 10ull, 0ull, 2ull), 1ull);

    EXPECT_FLOAT_EQ(Utils::RemapValue(5.f, Vector2(0.f, 10.f), Vector2(0.f, 1.f)), 0.5f);
    EXPECT_EQ(Utils::RemapValue(5ull, Vector2i(0, 10), Vector2i(0, 2)), 1ull);
}

TEST(Utils_Utils, NormalizeAngle)
{
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(0.f), 0.f);
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(Calc::TwoPi), 0.f);
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(-Calc::TwoPi), 0.f);

    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(Calc::Pi * 3.f), Calc::Pi);
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(5.f * Calc::PiOver2), Calc::PiOver2);

    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(-Calc::Pi), Calc::Pi);
    EXPECT_FLOAT_EQ(Utils::NormalizeAngle(-Calc::PiOver2), 3.f * Calc::PiOver2);
}

TEST(Utils_Utils, NormalizeAngles)
{
    constexpr Vector3 angles(Calc::TwoPi + 0.1f, -0.1f, Calc::Pi * 3.f);
    const Vector3 normalized = Utils::NormalizeAngles(angles);

    EXPECT_NEAR(normalized.x, 0.1f, 1e-6f);
    EXPECT_NEAR(normalized.y, Calc::TwoPi - 0.1f, 1e-6f);
    EXPECT_NEAR(normalized.z, Calc::Pi, 1e-6f);
}

TEST(Utils_Utils, DynamicPointerCast)
{
    struct A  // NOLINT(clang-diagnostic-padded)
    {
        s32 i = 1;

        A() = default;

        explicit A(const s32 i) : i(i) {}

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

TEST(Utils_Utils, StringArrayContains)
{
    constexpr std::array array{"Hello", ", ", "World", "!"};

    EXPECT_TRUE(Utils::StringArrayContains(array, "hello"));
    EXPECT_TRUE(Utils::StringArrayContains(array, "HELLO"));
    EXPECT_TRUE(Utils::StringArrayContains(array, "Hello"));
    EXPECT_FALSE(Utils::StringArrayContains(array, "string"));
}

TEST(Utils_Utils, StringEnumerableContains)
{
    constexpr Array array{"Hello", ", ", "World", "!"};

    EXPECT_TRUE(Utils::StringEnumerableContains(array, "hello"));
    EXPECT_TRUE(Utils::StringEnumerableContains(array, "HELLO"));
    EXPECT_TRUE(Utils::StringEnumerableContains(array, "Hello"));
    EXPECT_FALSE(Utils::StringEnumerableContains(array, "string"));
}

TEST(Utils_Utils, StringEqualsIgnoreCase)
{
    EXPECT_TRUE(Utils::StringEqualsIgnoreCase("hello", "HELLO"));
    EXPECT_TRUE(Utils::StringEqualsIgnoreCase("heLlO", "Hello"));
    EXPECT_FALSE(Utils::StringEqualsIgnoreCase("hello", "HELLO "));
}

TEST(Utils_Utils, StringContainsIgnoreCase)
{
    constexpr std::string_view str = "Hello, World!";

    EXPECT_TRUE(Utils::StringContainsIgnoreCase(str, "HELLO"));
    EXPECT_TRUE(Utils::StringContainsIgnoreCase(str, ","));
    EXPECT_FALSE(Utils::StringContainsIgnoreCase(str, "Hello world"));
}

namespace
{
    void Func(){}
}

TEST(Utils_Utils, FunctionAddress)
{
    EXPECT_EQ(reinterpret_cast<size_t>(&Func), Utils::FunctionAddress(std::function{Func}));
    EXPECT_NE(0ull, Utils::FunctionAddress(std::function{Func}));
}

TEST(Utils_Utils, CallSafe)
{
    const std::function<int()> null;
    const std::function<int()> nonnull = [] { return 1; };

    EXPECT_EQ(Utils::CallSafe(null), 0);
    EXPECT_EQ(Utils::CallSafe(nonnull), 1);
}

TEST(Utils_Utils, GetBits)
{
    constexpr u64 i = 0b01110000;

    auto result = Utils::GetBits<4, 1>(i);

    EXPECT_EQ(result, 0b00000001ull);

    result = Utils::GetBits<5, 3>(i);

    EXPECT_EQ(result, 0b00000011ull);
}

TEST(Utils_Utils, StringCase)
{
    EXPECT_EQ(Utils::ToLower("HeLLo"), "hello");
    EXPECT_EQ(Utils::ToUpper("HeLLo"), "HELLO");
}

TEST(Utils_Utils, Trim)
{
    EXPECT_EQ(Utils::Trim("  hello  ", Utils::TrimOptions::Both), "hello");
    EXPECT_EQ(Utils::Trim("  hello  ", Utils::TrimOptions::Start), "hello  ");
    EXPECT_EQ(Utils::Trim("  hello  ", Utils::TrimOptions::End), "  hello");
}

TEST(Utils_Utils, Split)
{
    const List<std::string> parts = Utils::Split("a,b,c", ',');
    EXPECT_EQ(parts.GetSize(), 3);
    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "b");
    EXPECT_EQ(parts[2], "c");
}

TEST(Utils_Utils, GetTypeHash)
{
    EXPECT_NE(Utils::GetTypeHash<int>(), 0);
    EXPECT_NE(Utils::GetTypeHash<float>(), 0);
    EXPECT_NE(Utils::GetTypeHash<int>(), Utils::GetTypeHash<float>());

    int i = 0;
    EXPECT_EQ(Utils::GetTypeHash<int>(), Utils::GetTypeHash(&i));
}

TEST(Utils_Utils, RemoveByteOrderMark)
{
    EXPECT_EQ(Utils::RemoveByteOrderMark("\xEF\xBB\xBFHello"), "Hello");
    EXPECT_EQ(Utils::RemoveByteOrderMark("Hello"), "Hello");
}

TEST(Utils_Utils, Concat)
{
    EXPECT_EQ(Utils::Concat16(0x01, 0x02), 0x0201);
    EXPECT_EQ(Utils::Concat32(0x01, 0x02, 0x03, 0x04), 0x04030201u);
}

TEST(Utils_Utils, ByteSizeUnit)
{
    const auto [val1, unit1] = Utils::ByteSizeUnit(500);
    EXPECT_FLOAT_EQ(val1, 500.f);
    EXPECT_EQ(unit1, "B");

    const auto [val2, unit2] = Utils::ByteSizeUnit(1500);
    EXPECT_FLOAT_EQ(val2, 1.5f);
    EXPECT_EQ(unit2, "KB");

    const auto [val3, unit3] = Utils::ByteSizeUnit(2500000);
    EXPECT_FLOAT_EQ(val3, 2.5f);
    EXPECT_EQ(unit3, "MB");
}

TEST(Utils_Utils, StringConversions)
{
    const std::string narrow = "Hello";
    const std::wstring wide = Utils::NarrowToWide(narrow);
    EXPECT_EQ(wide, L"Hello");

    const std::string back = Utils::WideToNarrow(wide);
    EXPECT_EQ(back, narrow);
}
