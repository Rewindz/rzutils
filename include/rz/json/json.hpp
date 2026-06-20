#pragma once

#include <concepts>
#include <filesystem>
#include <fstream>
#include <memory>

#include <nlohmann/json.hpp>

#include "../defs/defs.hpp"

namespace rz
{
    namespace json
    {
        template <typename T>
        concept JsonSerializable = requires(T t, nlohmann::json j) { j = t; };

        template <typename T>
        concept JsonDeserializable = std::default_initializable<T> &&
                                    requires(nlohmann::json j, T t) { j.get_to(t); };

        template <typename T>
        concept JsonAble = JsonSerializable<T> && JsonDeserializable<T>;

        template <JsonDeserializable T>
        EXPECTED_UPTR<T>
        LoadObjFromJsonFile_UPTR(const std::filesystem::path &_filePath,
                                const logCB &_logger = emptyCB)
        {
            if (!std::filesystem::exists(_filePath) ||
                !std::filesystem::is_regular_file(_filePath))
            {
                _logger(std::format("{} doesn't exist or isn't a regular file.\n",
                                    _filePath.string()));
                return std::unexpected(STATUS::RZ_ERROR);
            }

            try
            {
                std::ifstream inStream(_filePath);
                if (inStream.is_open())
                {
                    nlohmann::json j;
                    inStream >> j;
                    std::unique_ptr<T> uptr = std::make_unique<T>();
                    j.get_to(*uptr);
                    return std::move(uptr);
                } else {
                    _logger(std::format("Failed to open file {}.\n", _filePath.string()));
                    return std::unexpected(STATUS::RZ_ERROR);
                }
            }
            catch (const nlohmann::json::exception &e)
            {
                _logger(std::format("JSON error for file {}: {}\n", _filePath.string(),
                                    e.what()));
                return std::unexpected(STATUS::RZ_ERROR);
            }
        }

        template <JsonDeserializable T>
        EXPECTED_SPTR<T>
        LoadObjFromJsonFile_SPTR(const std::filesystem::path &_filePath,
                                const logCB &_logger = emptyCB)
        {
            if (!std::filesystem::exists(_filePath) ||
                !std::filesystem::is_regular_file(_filePath))
            {
                _logger(std::format("{} doesn't exist or isn't a regular file.\n",
                                    _filePath.string()));
                return std::unexpected(STATUS::RZ_ERROR);
            }

            try
            {
                std::ifstream inStream(_filePath);
                if (inStream.is_open())
                {
                    nlohmann::json j;
                    inStream >> j;
                    std::shared_ptr<T> sptr = std::make_shared<T>();
                    j.get_to(*sptr);
                    return sptr;
                } else {
                    _logger(std::format("Failed to open file {}.\n", _filePath.string()));
                    return std::unexpected(STATUS::RZ_ERROR);
                }
            }
            catch (const nlohmann::json::exception &e)
            {
                _logger(std::format("JSON error for file {}: {}\n", _filePath.string(),
                                    e.what()));
                return std::unexpected(STATUS::RZ_ERROR);
            }
        }

        template <JsonDeserializable T>
        EXPECTED_PTR<T>
        LoadObjFromJsonFile_PTR(const std::filesystem::path &_filePath,
                                const logCB &_logger = emptyCB)
        {
            if (!std::filesystem::exists(_filePath) ||
                !std::filesystem::is_regular_file(_filePath))
            {
                _logger(std::format("{} doesn't exist or isn't a regular file.\n",
                                    _filePath.string()));
                return std::unexpected(STATUS::RZ_ERROR);
            }

            try
            {
                std::ifstream inStream(_filePath);
                if (inStream.is_open())
                {
                    nlohmann::json j;
                    inStream >> j;
                    T* ptr = new T;
                    j.get_to(*ptr);
                    return ptr;
                } else {
                    _logger(std::format("Failed to open file {}.\n", _filePath.string()));
                    return std::unexpected(STATUS::RZ_ERROR);
                }
            }
            catch (const nlohmann::json::exception &e)
            {
                _logger(std::format("JSON error for file {}: {}\n", _filePath.string(),
                                    e.what()));
                return std::unexpected(STATUS::RZ_ERROR);
            }
        }

        template <JsonDeserializable T>
        EXPECTED_OBJ<T>
        LoadObjectFromJsonFile_OBJ(const std::filesystem::path &_filePath,
                                const logCB &_logger = emptyCB)
        {
            if (!std::filesystem::exists(_filePath) ||
                !std::filesystem::is_regular_file(_filePath))
            {
                _logger(std::format("{} doesn't exist or isn't a regular file.\n",
                                    _filePath.string()));
                return std::unexpected(STATUS::RZ_ERROR);
            }

            try
            {
                std::ifstream inStream(_filePath);
                if (inStream.is_open()) {
                    nlohmann::json j;
                    inStream >> j;
                    T t = j.get<T>();
                    return t;
                } else {
                    _logger(std::format("Failed to open file {}.\n", _filePath.string()));
                    return std::unexpected(STATUS::RZ_ERROR);
                }
            }
            catch (const nlohmann::json::exception &e)
            {
                _logger(std::format("JSON error for file {}: {}\n", _filePath.string(),
                                    e.what()));
                return std::unexpected(STATUS::RZ_ERROR);
            }
        }

        template <JsonDeserializable T>
        STATUS LoadObjectFromJsonFile_INPLACE(const std::filesystem::path &_filePath,
                                            T &_t, const logCB &_logger = emptyCB)
        {
            if (!std::filesystem::exists(_filePath) ||
                !std::filesystem::is_regular_file(_filePath))
            {
                _logger(std::format("{} doesn't exist or isn't a regular file.\n",
                                    _filePath.string()));
                return STATUS::RZ_ERROR;
            }
            try
            {
                std::ifstream inStream(_filePath);
                if (inStream.is_open()) {
                    nlohmann::json j;
                    inStream >> j;
                    j.get_to(_t);
                    return STATUS::RZ_SUCCESS;
                } else {
                    _logger(std::format("Failed to open file {}.\n", _filePath.string()));
                    return STATUS::RZ_ERROR;
                }
            }
            catch (const nlohmann::json::exception &e)
            {
                _logger(std::format("JSON error for file {}: {}\n", _filePath.string(),
                                    e.what()));
                return STATUS::RZ_ERROR;
            }
        }

        template <JsonSerializable T>
        STATUS WriteObjToJsonFile(const T &_t, const std::filesystem::path &_filePath,
                                int _indent = 4, const logCB &_logger = emptyCB)
        {
            if (std::filesystem::exists(_filePath) &&
                !std::filesystem::is_regular_file(_filePath))
            {
                _logger(std::format("{} exists and is not a regular file.\n",
                                    _filePath.string()));
                return STATUS::RZ_ERROR;
            }

            try {
                nlohmann::json j = _t;
                std::ofstream outStream(_filePath);
                if (outStream.is_open()) {
                    outStream << j.dump(_indent);
                    return STATUS::RZ_SUCCESS;
                } else {
                    _logger(std::format("Failed to open file {}.\n", _filePath.string()));
                    return STATUS::RZ_ERROR;
                }
            } catch (const nlohmann::json::exception &e) {
                _logger(std::format("JSON error for file {}: {}\n", _filePath.string(),
                                    e.what()));
                return STATUS::RZ_ERROR;
            }
        }

    } // namespace json
} // namespace rz
