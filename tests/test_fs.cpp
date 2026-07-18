#include <gtest/gtest.h>

#include <rz/fs/fs.hpp>
#include <rz/defs/defs.hpp>
#include <string>
#include <iostream>

TEST(FS, GetAppConfigPath)
{
    using namespace rz;

    auto res = fs::GetAppConfigPath("test_app", [](const std::string& log){
        std::cerr << log << std::endl;
    });
    EXPECT_TRUE(res.has_value());
}
