#include "PrecompiledHeader.hpp"

#include <Mountain/Utils/Color.hpp>

using namespace Mountain;

TEST(Utils_Color, Constructors)
{
    const Color c1;
    EXPECT_FLOAT_EQ(c1.r, 0.f);
    EXPECT_FLOAT_EQ(c1.g, 0.f);
    EXPECT_FLOAT_EQ(c1.b, 0.f);
    EXPECT_FLOAT_EQ(c1.a, 1.f);

    const Color c2(0.5f, 0.2f);
    EXPECT_FLOAT_EQ(c2.r, 0.5f);
    EXPECT_FLOAT_EQ(c2.g, 0.5f);
    EXPECT_FLOAT_EQ(c2.b, 0.5f);
    EXPECT_FLOAT_EQ(c2.a, 0.2f);

    const Color c3(1.f, 0.f, 0.f, 0.5f);
    EXPECT_FLOAT_EQ(c3.r, 1.f);
    EXPECT_FLOAT_EQ(c3.g, 0.f);
    EXPECT_FLOAT_EQ(c3.b, 0.f);
    EXPECT_FLOAT_EQ(c3.a, 0.5f);
}

TEST(Utils_Color, Constants)
{
    EXPECT_EQ(Color::Red().GetPackedValue(), 0xFF0000FF);
    EXPECT_EQ(Color::Green().GetPackedValue(), 0xFF008000);
    EXPECT_EQ(Color::Blue().GetPackedValue(), 0xFFFF0000);
    EXPECT_EQ(Color::White().GetPackedValue(), 0xFFFFFFFF);
    EXPECT_EQ(Color::Black().GetPackedValue(), 0xFF000000);
    EXPECT_EQ(Color::Transparent().GetPackedValue(), 0x00000000);
}

TEST(Utils_Color, Packing)
{
    const Color c(1.f, 0.5f, 0.25f, 1.f);
    const u32 packed = c.GetPackedValue();
    const Color unpacked(packed);

    // Tolerance due to 8-bit quantization
    EXPECT_NEAR(unpacked.r, c.r, 1.f / 255.f);
    EXPECT_NEAR(unpacked.g, c.g, 1.f / 255.f);
    EXPECT_NEAR(unpacked.b, c.b, 1.f / 255.f);
    EXPECT_NEAR(unpacked.a, c.a, 1.f / 255.f);
}

TEST(Utils_Color, Hex)
{
    const Color c = Color::FromHex(0xFF00AA55); // RGBA
    EXPECT_FLOAT_EQ(c.r, 1.f);
    EXPECT_FLOAT_EQ(c.g, 0.f);
    EXPECT_NEAR(c.b, 170.f / 255.f, 1e-6f);
    EXPECT_NEAR(c.a, 85.f / 255.f, 1e-6f);
}

TEST(Utils_Color, Arithmetic)
{
    const Color c1(0.1f, 0.2f, 0.3f, 0.4f);
    const Color c2(0.5f, 0.5f, 0.5f, 0.5f);

    const Color sum = c1 + c2;
    // Expected: 0.6, 0.7, 0.8, 0.9
    EXPECT_NEAR(sum.r, 0.6f, 1e-1f);
    EXPECT_NEAR(sum.g, 0.7f, 1e-1f);
    EXPECT_NEAR(sum.b, 0.8f, 1e-1f);
    EXPECT_NEAR(sum.a, 0.9f, 1e-1f);

    const Color prod = c1 * c2;
    // Expected: 0.05, 0.1, 0.15, 0.2
    EXPECT_NEAR(prod.r, 0.05f, 1e-1f);
    EXPECT_NEAR(prod.a, 0.2f, 1e-1f);

    const Color factor = c1 * 2.f;
    // Expected: 0.2, 0.4, 0.6, 0.8
    EXPECT_NEAR(factor.r, 0.2f, 1e-1f);
    EXPECT_NEAR(factor.a, 0.8f, 1e-1f);
}

TEST(Utils_Color, HSVA)
{
    const Color rgb = Color::Red();
    const ColorHsva hsva = rgb.ToHsva();

    EXPECT_NEAR(hsva.h, 0.f, 1e-6f);
    EXPECT_NEAR(hsva.s, 1.f, 1e-6f);
    EXPECT_NEAR(hsva.v, 1.f, 1e-6f);
    EXPECT_NEAR(hsva.a, 1.f, 1e-6f);

    const Color back = hsva.ToRgba();
    EXPECT_EQ(rgb.GetPackedValue(), back.GetPackedValue());

    const ColorHsva blueHsva(240.f / 360.f, 1.f, 1.f, 1.f);
    EXPECT_EQ(blueHsva.ToRgba().GetPackedValue(), Color::Blue().GetPackedValue());
}

TEST(Utils_Color, Lerp)
{
    const Color c1 = Color::Black();
    const Color c2 = Color::White();

    const Color middle = Calc::Lerp(c1, c2, 0.5f);
    EXPECT_FLOAT_EQ(middle.r, 0.5f);
    EXPECT_FLOAT_EQ(middle.g, 0.5f);
    EXPECT_FLOAT_EQ(middle.b, 0.5f);
    EXPECT_FLOAT_EQ(middle.a, 1.f);
}
