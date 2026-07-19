#include <gtest/gtest.h>

#include <rz/fs/fs.hpp>
#include <rz/defs/defs.hpp>

TEST(FS, GetAppConfigPath)
{
    using namespace rz;

    auto res = fs::GetAppConfigPath("test_app", stderrCB);
    EXPECT_TRUE(res.has_value());
}
