#include "rz/math/mat.hpp"
#include <gtest/gtest.h>
#include <rz/math/math.hpp>
#include <rz/math/vec.hpp>
#include <type_traits>

TEST(MathTest, Vec3_DotProduct) {
    rz::math::Vec3f a(1.0f, 2.0f, 3.0f);
    rz::math::Vec3f b(4.0f, 5.0f, 6.0f);

    float expected = (1.0f * 4.0f) + (2.0f * 5.0f) + (3.0f * 6.0f);
    EXPECT_FLOAT_EQ(a.dot(b), expected);
}

TEST(MathTest, Vec3_Normalization) {
    rz::math::Vec3f v(3.0f, 0.0f, 4.0f);

    EXPECT_FLOAT_EQ(v.mag(), 5.0f);

    v.normalize();

    EXPECT_FLOAT_EQ(v.x, 3.0f / 5.0f);
    EXPECT_FLOAT_EQ(v.z, 4.0f / 5.0f);
    EXPECT_FLOAT_EQ(v.mag(), 1.0f);
}

TEST(MathTest, Vec2_Equality) {
    rz::math::Vec2i v1(10, 20);
    rz::math::Vec2i v2(10, 20);
    rz::math::Vec2i v3(10, 21);

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(MathTest, Vec2_OperatorBracket) {
    rz::math::Vec2f v(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);

    v[0] = 10.0f;
    EXPECT_FLOAT_EQ(v.x, 10.0f);

    static_assert(std::is_same_v<decltype(v[0]), float&>, "Failed: Did not return float&");

    const rz::math::Vec2f cv(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(cv[0], 3.0f);
    EXPECT_FLOAT_EQ(cv[1], 4.0f);

    static_assert(std::is_same_v<decltype(cv[0]), const float&>, "Failed: Did not return const float&");

    EXPECT_FLOAT_EQ(rz::math::Vec2f(5.0f, 6.0f)[1], 6.0f);

    static_assert(std::is_same_v<decltype(rz::math::Vec2f(0.0f, 0.0f)[0]), float&&>, "Failed: Did not return float&&");
}

TEST(MathTest, Vec3_OperatorBracket) {
    rz::math::Vec3f v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);

    v[2] = 30.0f;
    EXPECT_FLOAT_EQ(v.z, 30.0f);
    static_assert(std::is_same_v<decltype(v[0]), float&>);

    const rz::math::Vec3f cv(4.0f, 5.0f, 6.0f);
    EXPECT_FLOAT_EQ(cv[0], 4.0f);
    EXPECT_FLOAT_EQ(cv[1], 5.0f);
    EXPECT_FLOAT_EQ(cv[2], 6.0f);
    static_assert(std::is_same_v<decltype(cv[0]), const float&>);

    EXPECT_FLOAT_EQ(rz::math::Vec3f(7.0f, 8.0f, 9.0f)[2], 9.0f);
    static_assert(std::is_same_v<decltype(rz::math::Vec3f()[0]), float&&>);
}

TEST(MathTest, Vec4_OperatorBracket) {
    rz::math::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
    EXPECT_FLOAT_EQ(v[3], 4.0f);

    v[3] = 40.0f;
    EXPECT_FLOAT_EQ(v.w, 40.0f);
    static_assert(std::is_same_v<decltype(v[0]), float&>);

    const rz::math::Vec4f cv(5.0f, 6.0f, 7.0f, 8.0f);
    EXPECT_FLOAT_EQ(cv[0], 5.0f);
    EXPECT_FLOAT_EQ(cv[1], 6.0f);
    EXPECT_FLOAT_EQ(cv[2], 7.0f);
    EXPECT_FLOAT_EQ(cv[3], 8.0f);
    static_assert(std::is_same_v<decltype(cv[0]), const float&>);

    EXPECT_FLOAT_EQ(rz::math::Vec4f(9.0f, 10.0f, 11.0f, 12.0f)[3], 12.0f);
    static_assert(std::is_same_v<decltype(rz::math::Vec4f()[0]), float&&>);
}

TEST(MathTest, Mat4_Identity) {
    rz::math::Mat4f identity = rz::math::Mat4f::Identity();
    EXPECT_FLOAT_EQ(identity(0, 0),  1.0f);
    EXPECT_FLOAT_EQ(identity(1, 1),  1.0f);
    EXPECT_FLOAT_EQ(identity(2, 2), 1.0f);
    EXPECT_FLOAT_EQ(identity(3, 3), 1.0f);
}
