#pragma once
#include <filesystem>
#include <string>

#include "../defs/defs.hpp"

namespace rz
{
    namespace fs
    {

        #ifdef __linux__
        EXPECTED_OBJ<std::filesystem::path> GetHomePath(logCB _logger = emptyCB);
        #endif

        EXPECTED_OBJ<std::filesystem::path> GetAppConfigPath(const std::string& _appname, logCB _logger = emptyCB);

        inline bool ExistsAndIsRegularFile(const std::filesystem::path& _path)
        {
            return std::filesystem::exists(_path) && std::filesystem::is_regular_file(_path);
        }

        inline bool ExistsAndIsDirectory(const std::filesystem::path& _path)
        {
            return std::filesystem::exists(_path) && std::filesystem::is_directory(_path);
        }

        inline bool ExistsAndIsSymlink(const std::filesystem::path& _path)
        {
            return std::filesystem::exists(_path) && std::filesystem::is_symlink(_path);
        }

    } // namespace fs
} // namespace rz
