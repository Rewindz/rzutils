#pragma once

#include <filesystem>
#include <memory>
#include <utility>

#include "./json.hpp"
#include "../defs/defs.hpp"

namespace rz
{

template <JsonAble T>
class Saveable
{
public:

    Saveable() = delete;
    Saveable(Saveable&) = delete;
    Saveable& operator=(Saveable&) = delete;
    Saveable(Saveable&&) noexcept = default;
    Saveable& operator=(Saveable&&) noexcept = default;


    Saveable(const std::filesystem::path& _path, int _indent = -1, logCB _logger = emptyCB)
        : path(_path), indent(_indent), logger(_logger)
    {
        obj = std::make_unique<T>();
    }

    Saveable(const std::filesystem::path& _path, std::unique_ptr<T> _obj, logCB _logger = emptyCB)
        : path(_path), obj(std::move(_obj)), logger(_logger)
    {}

    STATUS Save()
    {
        return WriteObjToJsonFile(*obj, path, indent, logger);
    }

    STATUS Load()
    {
        return LoadObjectFromJsonFile_INPLACE(path, *obj, logger);
    }

    T& operator*()
    {
        return *obj;
    }

    const T& operator*() const
    {
        return *obj;
    }

    T* operator->() const
    {
        return obj.get();
    }

private:

    int indent;
    std::unique_ptr<T> obj;
    std::filesystem::path path;
    logCB logger;

};

} // namespace rz
