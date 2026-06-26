#include <gtest/gtest.h>
#include <rz/math/vec.hpp>

TEST(MathTest, Vec3DotProduct) {
    rz::math::Vec3f a(1.0f, 2.0f, 3.0f);
    rz::math::Vec3f b(4.0f, 5.0f, 6.0f);

    float expected = (1.0f * 4.0f) + (2.0f * 5.0f) + (3.0f * 6.0f);
    EXPECT_FLOAT_EQ(a.dot(b), expected);
}

TEST(MathTest, Vec3Normalization) {
    rz::math::Vec3f v(3.0f, 0.0f, 4.0f);

    EXPECT_FLOAT_EQ(v.mag(), 5.0f);

    v.normalize();

    EXPECT_FLOAT_EQ(v.x, 3.0f / 5.0f);
    EXPECT_FLOAT_EQ(v.z, 4.0f / 5.0f);
    EXPECT_FLOAT_EQ(v.mag(), 1.0f);
}

TEST(MathTest, Vec2Equality) {
    rz::math::Vec2i v1(10, 20);
    rz::math::Vec2i v2(10, 20);
    rz::math::Vec2i v3(10, 21);

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}
