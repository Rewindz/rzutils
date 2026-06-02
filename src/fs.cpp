#include "rz/fs/fs.hpp"

#include <cstdlib>

namespace rz
{
    namespace fs
    {

        #ifdef __linux__
        EXPECTED_OBJ<std::filesystem::path> GetHomePath(logCB _logger)
        {
            const char* homeCStr = std::getenv("HOME");
            if(!homeCStr){
                _logger("Failed to find HOME.");
                return std::unexpected(STATUS::RZ_ERROR);
            }
            return std::filesystem::path(homeCStr);
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
