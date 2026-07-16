#include <gtest/gtest.h>

#include <string>
#include <rz/string/utils.hpp>

TEST(StringTest, iequal)
{
    std::string a = "Hello World!";
    std::string b = "hello world!";

    EXPECT_TRUE(rz::string::iequal(a, b));

    std::string c = "Hello World!";
    std::string d = "Hello World!";
    EXPECT_TRUE(rz::string::iequal(c, d));

    std::string e = "Hello World!";
    std::string f = "ello World!";
    EXPECT_FALSE(rz::string::iequal(e, f));

    std::string g = "";
    std::string h = "a";
    EXPECT_FALSE(rz::string::iequal(g, h));

}
