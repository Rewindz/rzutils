#include <nlohmann/json.hpp>
#include <rz/defs/defs.hpp>
#include <gtest/gtest.h>
#include <rz/json/json.hpp>

#include <string>
#include <filesystem>

struct TestConfig {
    int res_x = 1920;
    int res_y = 1080;
    std::string title = "Test";
    auto operator<=>(const TestConfig&) const = default;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TestConfig, res_x, res_y, title)

TEST(JsonTest, WriteAndReadConfig) {
    TestConfig original_cfg{2560, 1440, "Test 1"};
    std::filesystem::path temp_file = std::filesystem::temp_directory_path() / "test_cfg.json";

    rz::STATUS write_status = rz::json::WriteObjToJsonFile(original_cfg, temp_file);
    EXPECT_EQ(write_status, rz::STATUS::RZ_SUCCESS);
    EXPECT_TRUE(std::filesystem::exists(temp_file));

    auto loaded_cfg_expected = rz::json::LoadObjectFromJsonFile_OBJ<TestConfig>(temp_file);

    ASSERT_TRUE(loaded_cfg_expected.has_value());

    EXPECT_EQ(loaded_cfg_expected->res_x, 2560);
    EXPECT_EQ(loaded_cfg_expected->title, "Test 1");

    std::filesystem::remove(temp_file);
}

TEST(JsonTest, FailGracefullyOnMissingFile) {
    std::filesystem::path bad_path = "does_not_exists.json";
    auto result = rz::json::LoadObjectFromJsonFile_OBJ<TestConfig>(bad_path);

    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), rz::STATUS::RZ_ERROR);
}
