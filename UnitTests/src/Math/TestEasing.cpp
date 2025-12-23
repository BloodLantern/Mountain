#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

TEST(Easing, Linear)
{
    EXPECT_EQ(Easing::Linear(0.f), 0.f);
    EXPECT_EQ(Easing::Linear(0.5f), 0.5f);
    EXPECT_EQ(Easing::Linear(1.f), 1.f);
}

TEST(Easing, Sine)
{
    EXPECT_EQ(Easing::SineIn(0.f), 0.f);
    EXPECT_NEAR(Easing::SineIn(1.f), 1.f, 1e-4f);

    EXPECT_EQ(Easing::SineOut(0.f), 0.f);
    EXPECT_NEAR(Easing::SineOut(1.f), 1.f, 1e-4f);

    EXPECT_EQ(Easing::SineInOut(0.f), 0.f);
    EXPECT_NEAR(Easing::SineInOut(1.f), 1.f, 1e-4f);
}

TEST(Easing, Quad)
{
    EXPECT_EQ(Easing::QuadIn(0.f), 0.f);
    EXPECT_EQ(Easing::QuadIn(0.5f), 0.25f);
    EXPECT_EQ(Easing::QuadIn(1.f), 1.f);

    EXPECT_EQ(Easing::QuadOut(0.f), 0.f);
    EXPECT_EQ(Easing::QuadOut(0.5f), 0.75f);
    EXPECT_EQ(Easing::QuadOut(1.f), 1.f);

    EXPECT_EQ(Easing::QuadInOut(0.f), 0.f);
    EXPECT_EQ(Easing::QuadInOut(0.5f), 0.5f);
    EXPECT_EQ(Easing::QuadInOut(1.f), 1.f);
}

TEST(Easing, Cubic)
{
    EXPECT_NEAR(Easing::CubicIn(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::CubicIn(0.5f), 0.125f, 1e-4f);
    EXPECT_NEAR(Easing::CubicIn(1.f), 1.f, 1e-4f);

    EXPECT_NEAR(Easing::CubicOut(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::CubicOut(0.5f), 0.875f, 1e-4f);
    EXPECT_NEAR(Easing::CubicOut(1.f), 1.f, 1e-4f);

    EXPECT_NEAR(Easing::CubicInOut(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::CubicInOut(0.5f), 0.5f, 1e-4f);
    EXPECT_NEAR(Easing::CubicInOut(1.f), 1.f, 1e-4f);
}

TEST(Easing, Quart)
{
    EXPECT_EQ(Easing::QuartIn(0.f), 0.f);
    EXPECT_EQ(Easing::QuartIn(1.f), 1.f);

    EXPECT_EQ(Easing::QuartOut(0.f), 0.f);
    EXPECT_EQ(Easing::QuartOut(1.f), 1.f);

    EXPECT_EQ(Easing::QuartInOut(0.f), 0.f);
    EXPECT_EQ(Easing::QuartInOut(0.5f), 0.5f);
    EXPECT_EQ(Easing::QuartInOut(1.f), 1.f);
}

TEST(Easing, Quint)
{
    EXPECT_EQ(Easing::QuintIn(0.f), 0.f);
    EXPECT_EQ(Easing::QuintIn(1.f), 1.f);

    EXPECT_EQ(Easing::QuintOut(0.f), 0.f);
    EXPECT_EQ(Easing::QuintOut(1.f), 1.f);

    EXPECT_EQ(Easing::QuintInOut(0.f), 0.f);
    EXPECT_EQ(Easing::QuintInOut(0.5f), 0.5f);
    EXPECT_EQ(Easing::QuintInOut(1.f), 1.f);
}

TEST(Easing, Expo)
{
    EXPECT_NEAR(Easing::ExpoIn(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::ExpoIn(1.f), 1.f, 1e-4f);

    EXPECT_NEAR(Easing::ExpoOut(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::ExpoOut(1.f), 1.f, 1e-4f);

    EXPECT_NEAR(Easing::ExpoInOut(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::ExpoInOut(1.f), 1.f, 1e-4f);
}

TEST(Easing, Circ)
{
    EXPECT_EQ(Easing::CircIn(0.f), 0.f);
    EXPECT_EQ(Easing::CircIn(1.f), 1.f);

    EXPECT_EQ(Easing::CircOut(0.f), 0.f);
    EXPECT_EQ(Easing::CircOut(1.f), 1.f);

    EXPECT_EQ(Easing::CircInOut(0.f), 0.f);
    EXPECT_EQ(Easing::CircInOut(1.f), 1.f);
}

TEST(Easing, Back)
{
    EXPECT_EQ(Easing::BackIn(0.f), 0.f);
    EXPECT_EQ(Easing::BackIn(1.f), 1.f);

    EXPECT_EQ(Easing::BackOut(0.f), 0.f);
    EXPECT_EQ(Easing::BackOut(1.f), 1.f);

    EXPECT_EQ(Easing::BackInOut(0.f), 0.f);
    EXPECT_EQ(Easing::BackInOut(1.f), 1.f);
}

TEST(Easing, Elastic)
{
    EXPECT_EQ(Easing::ElasticIn(0.f), 0.f);
    EXPECT_NEAR(Easing::ElasticIn(1.f), 1.f, 1e-4f);

    EXPECT_EQ(Easing::ElasticOut(0.f), 0.f);
    EXPECT_NEAR(Easing::ElasticOut(1.f), 1.f, 1e-4f);

    EXPECT_EQ(Easing::ElasticInOut(0.f), 0.f);
    EXPECT_NEAR(Easing::ElasticInOut(1.f), 1.f, 1e-4f);
}

TEST(Easing, Bounce)
{
    EXPECT_NEAR(Easing::BounceIn(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::BounceIn(1.f), 1.f, 1e-4f);

    EXPECT_NEAR(Easing::BounceOut(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::BounceOut(1.f), 1.f, 1e-4f);

    EXPECT_NEAR(Easing::BounceInOut(0.f), 0.f, 1e-4f);
    EXPECT_NEAR(Easing::BounceInOut(1.f), 1.f, 1e-4f);
}
