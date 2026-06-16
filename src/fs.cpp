#include "rz/fs/fs.hpp"

#include <cstdlib>
#include <expected>

namespace rz
{
    namespace fs
    {

        #if defined(__linux__) || defined(__APPLE__)
        EXPECTED_OBJ<std::filesystem::path> GetHomePath(logCB _logger)
        {
            const char* homeCStr = std::getenv("HOME");
            if(!homeCStr){
                _logger("Failed to find HOME.");
                return std::unexpected(STATUS::RZ_ERROR);
            }
            return std::filesystem::path(homeCStr);
        }
        #else
        EXPECTED_OBJ<std::filesystem::path> GetHomePath(logCB _logger)
        {
            _logger("GetHomePath not implemented for this OS.");
            return std::unexpected(STATUS::RZ_ERROR);
        }
        #endif

        EXPECTED_OBJ<std::filesystem::path> GetAppConfigPath(const std::string& _appname, logCB _logger)
        {
            #ifdef __linux__

            auto homePath = GetHomePath(_logger);
            if(!homePath){
                return std::unexpected(STATUS::RZ_ERROR);
            }

            return std::filesystem::path(*homePath / ".config" / _appname);

            #elifdef _WIN32

            const char* appdataCStr = std::getenv("APPDATA");
            if(!appdataCStr){
                _logger("Failed to find APPDATA");
                return std::unexpected(STATUS::RZ_ERROR);
            }

            return std::filesystem::path(appdataCStr) / std::filesystem::path(_appname);

            #endif

            _logger("GetAppConfigPath not implemented for this OS.");
            return std::unexpected(STATUS::RZ_ERROR);
        }

        bool ExistsAndIsRegularFile(const std::filesystem::path& _path)
        {
            return std::filesystem::exists(_path) && std::filesystem::is_regular_file(_path);
        }

        bool ExistsAndIsDirectory(const std::filesystem::path& _path)
        {
            return std::filesystem::exists(_path) && std::filesystem::is_directory(_path);
        }

        bool ExistsAndIsSymlink(const std::filesystem::path& _path)
        {
            return std::filesystem::exists(_path) && std::filesystem::is_symlink(_path);
        }

    } // namespace fs
} // namespace rz
