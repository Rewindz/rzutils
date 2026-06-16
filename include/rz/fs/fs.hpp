#pragma once
#include <filesystem>
#include <string>

#include "../defs/defs.hpp"

namespace rz
{
    namespace fs
    {

        EXPECTED_OBJ<std::filesystem::path> GetHomePath(logCB _logger = emptyCB);
        EXPECTED_OBJ<std::filesystem::path> GetAppConfigPath(const std::string& _appname, logCB _logger = emptyCB);

        bool ExistsAndIsRegularFile(const std::filesystem::path& _path);
        bool ExistsAndIsDirectory(const std::filesystem::path& _path);
        bool ExistsAndIsSymlink(const std::filesystem::path& _path);

    } // namespace fs
} // namespace rz
