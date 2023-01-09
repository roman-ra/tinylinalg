#include "gtest/gtest.h"

#include "tinylinalg/Vector.hpp"

using namespace tla;

TEST(VectorTest, Vector2Constructors)
{
    vec2 a;
    vec2 b{42.f};
    vec2 c{42.f, 84.f};
    EXPECT_TRUE(a.x == 0.f && a.y == 0.f);
    EXPECT_TRUE(b.x == 42.f && b.y == 42.f);
    EXPECT_TRUE(c.x == 42.f && c.y == 84.f);
}

TEST(VectorTest, Vector3Constructors)
{
    vec3 a;
    vec3 b{42.f};
    vec3 c{42.f, 84.f, 126.f};
    EXPECT_TRUE(a.x == 0.f && a.y == 0.f && a.z == 0.f);
    EXPECT_TRUE(b.x == 42.f && b.y == 42.f && b.z == 42.f);
    EXPECT_TRUE(c.x == 42.f && c.y == 84.f && c.z == 126.f);
}

TEST(VectorTest, Vector4Constructors)
{
    vec4 a;
    vec4 b{42.f};
    vec4 c{42.f, 84.f, 126.f, 168.f};
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

TEST(VectorTest, Equality)
{
    tla::Vector<float, 5> a;
    tla::Vector<float, 5> b{42.f};
    tla::Vector<float, 5> c{42.f, 42.f, 42.f, 42.f, 42.f};

    EXPECT_NE(a, b);
    EXPECT_EQ(b, c);
}

TEST(VectorTest, UnaryMinus)
{
    tla::Vector<float, 5> a{1.f};
    tla::Vector<float, 5> a_target{-1.f};

    auto a_neg = -a;

    EXPECT_EQ(a_neg, a_target);

    ivec2 b{-3};
    ivec2 b_target{3};

    auto b_neg = -b;

    EXPECT_EQ(b_neg, b_target);
}

TEST(VectorTest, BinaryVectorVectorOperators)
{
    tla::Vector2d a{1., 2.};
    tla::Vector2d b{3., 4.};

    tla::Vector2d a_plus_b{1. + 3., 2. + 4.};
    tla::Vector2d a_minus_b{1. - 3., 2. - 4.};
    tla::Vector2d a_mul_b{1. * 3., 2. * 4.};
    tla::Vector2d a_div_b{1. / 3., 2. / 4.};
    double a_dot_b{1. * 3. + 2. * 4.};

    EXPECT_EQ(a + b, a_plus_b);
    EXPECT_EQ(a - b, a_minus_b);
    EXPECT_EQ(a * b, a_mul_b);
    EXPECT_EQ(a / b, a_div_b);
    EXPECT_EQ(tla::dot(a, b), a_dot_b);
}

TEST(VectorTest, BinaryVectorScalarOperators)
{
    tla::Vector2d a{1., 2.};
    double s{3.};

    tla::Vector2d a_plus_s{1. + 3., 2. + 3.};
    tla::Vector2d a_minus_s{1. - 3., 2. - 3.};
    tla::Vector2d a_mul_s{1. * 3., 2. * 3.};
    tla::Vector2d a_div_s{1. / 3., 2. / 3.};

    EXPECT_EQ(a + s, a_plus_s);
    EXPECT_EQ(a - s, a_minus_s);
    EXPECT_EQ(a * s, a_mul_s);
    EXPECT_EQ(a / s, a_div_s);

    tla::Vector2d s_plus_a{3. + 1., 3. + 2.};
    tla::Vector2d s_minus_a{3. - 1., 3. - 2.};
    tla::Vector2d s_mul_a{3. * 1., 3. * 2.};
    tla::Vector2d s_div_a{3. / 1., 3. / 2.};

    EXPECT_EQ(s + a, s_plus_a);
    EXPECT_EQ(s - a, s_minus_a);
    EXPECT_EQ(s * a, s_mul_a);
    EXPECT_EQ(s / a, s_div_a);
}