#include "gtest/gtest.h"

#include "tinylinalg/Vector.hpp"

#include <iostream>

TEST(VectorTest, Vector2Constructors)
{
    tla::Vector2f a;
    tla::Vector2f b{42.f};
    tla::Vector2f c{42.f, 84.f};
    EXPECT_TRUE(a.x == 0.f && a.y == 0.f);
    EXPECT_TRUE(b.x == 42.f && b.y == 42.f);
    EXPECT_TRUE(c.x == 42.f && c.y == 84.f);
}

TEST(VectorTest, Vector3Constructors)
{
    tla::Vector3f a;
    tla::Vector3f b{42.f};
    tla::Vector3f c{42.f, 84.f, 126.f};
    EXPECT_TRUE(a.x == 0.f && a.y == 0.f && a.z == 0.f);
    EXPECT_TRUE(b.x == 42.f && b.y == 42.f && b.z == 42.f);
    EXPECT_TRUE(c.x == 42.f && c.y == 84.f && c.z == 126.f);
}

TEST(VectorTest, Vector4Constructors)
{
    tla::Vector4f a;
    tla::Vector4f b{42.f};
    tla::Vector4f c{42.f, 84.f, 126.f, 168.f};
    EXPECT_TRUE(a.x == 0.f && a.y == 0.f && a.z == 0.f && a.w == 0.f);
    EXPECT_TRUE(b.x == 42.f && b.y == 42.f && b.z == 42.f && b.w == 42.f);
    EXPECT_TRUE(c.x == 42.f && c.y == 84.f && c.z == 126.f && c.w == 168.f);
}

TEST(VectorTest, VectorGenericConstructors)
{
    tla::Vector<double, 10> a;
    tla::Vector<double, 10> b{42.};
    tla::Vector<double, 10> c{1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(a[i] == 0.);
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(b[i] == 42.);
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(c[i] == static_cast<double>(i + 1));
    }
}

TEST(VectorTest, VectorEquality)
{
    tla::Vector<float, 5> a;
    tla::Vector<float, 5> b{42.f};
    tla::Vector<float, 5> c{42.f, 42.f, 42.f, 42.f, 42.f};

    EXPECT_NE(a, b);
    EXPECT_EQ(b, c);
}

TEST(VectorTest, VectorUnaryMinus)
{
    tla::Vector<float, 5> a{1.f};
    tla::Vector<float, 5> a_target{-1.f};

    auto a_neg = -a;

    EXPECT_EQ(a_neg, a_target);

    tla::Vector2i b{-3};
    tla::Vector2i b_target{3};

    auto b_neg = -b;

    EXPECT_EQ(b_neg, b_target);
}